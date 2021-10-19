#include <iostream>
#include <memory>
#include <string>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include <thread>
#include <vector>

#include "proto/keyvalue.grpc.pb.h"
#include "service/KeyValueCallDatServiceImpl.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using keyvaluestore::KeyValueStore;


class KeyValueServerImpl final {
private:
    // This can be run in multiple threads if needed.
    void HandleRpcCalls(int cq_index) {

        int policyType = configMap["CACHE_REPLACEMENT_TYPE"];
        if (policyType == 1) {
            INFO("KVServer", "LRU Policy Selected");
            new GetCallData(&asyncService, completionQueueList[cq_index].get(), lruCache);
            new DelCallData(&asyncService, completionQueueList[cq_index].get(), lruCache);
            new PutCallData(&asyncService, completionQueueList[cq_index].get(), lruCache);
        } else {
            INFO("KVServer", "LFU Policy Selected");
            new GetCallData(&asyncService, completionQueueList[cq_index].get(), lfuCache);
            new DelCallData(&asyncService, completionQueueList[cq_index].get(), lfuCache);
            new PutCallData(&asyncService, completionQueueList[cq_index].get(), lfuCache);
        }
        // Spawn a new CallData instance to serve new clients.

        void *tag;  // uniquely identifies a request.
        bool ok;
        while (true) {
            // Block waiting to read the next event from the completion queue. The
            // event is uniquely identified by its tag, which in this case is the
            // memory address of a CallData instance.
            // The return value of Next should always be checked. This return value
            // tells us whether there is any kind of event or completionQueue is shutting down.
            GPR_ASSERT(completionQueueList[cq_index]->Next(&tag, &ok));

            //Confirming if the fetching from the queue is successful or not
            GPR_ASSERT(ok);

            //type-casting the respective call and proceeding the next process.
            static_cast<CallData *>(tag)->Proceed();

        }
    }

    KeyValueStore::AsyncService asyncService;
    std::unique_ptr<Server> server;
    std::map<std::string, int> configMap;
    std::vector<std::unique_ptr<ServerCompletionQueue>> completionQueueList;
    LRUCache *lruCache;
    LFUCache *lfuCache;

public:
    ~KeyValueServerImpl() {
        server->Shutdown();
        // Always shutdown the completion queue after the server.
        for(const auto& cq: completionQueueList){
            cq->Shutdown();
        }
    }

    // There is no shutdown handling in this code.
    void Run() {
        FileService *fileService = new FileService();
        configMap = fileService->getConfig();
        std::string server_address("localhost:" + to_string(configMap["LISTENING_PORT"]));
        lfuCache = new LFUCache(configMap["CACHE_SIZE"]);
        lruCache = new LRUCache(configMap["CACHE_SIZE"]);

        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "asyncService" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *asynchronous* service.
        builder.RegisterService(&asyncService);
        // Get hold of the completion queue used for the asynchronous communication
        // with the gRPC runtime.
        for (auto i = 0; i < configMap["COMPLETION_QUEUE"]; i++) {
            INFO("KVServer", "Initialize completion queue:" + to_string(i));
            completionQueueList.emplace_back(builder.AddCompletionQueue());
        }

        // Finally assemble the server.
        server = builder.BuildAndStart();

        WARN("KVServer", " Server listening on " + server_address);

        std::vector<std::thread *> _threads;

        for (auto i = 0; i < configMap["THREAD_POOL_SIZE"]; i++) {
            int cq_index = i % configMap["COMPLETION_QUEUE"];
            _threads.emplace_back(new std::thread(&KeyValueServerImpl::HandleRpcCalls, this, cq_index));
        }
        WARN("KVServer", to_string(configMap["THREAD_POOL_SIZE"]) + " working async threads spawned");

        for (const auto &_t: _threads) {
            _t->join();
        }
    }

};

int main(int argc, char **argv) {
    KeyValueServerImpl server;
    server.Run();

    return 0;
}