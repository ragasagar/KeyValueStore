#include <iostream>
#include <memory>
#include <string>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "proto/keyvalue.grpc.pb.h"
#include "service/KeyValueCallDatServiceImpl.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using keyvaluestore::KeyValueStore;


class KeyValueServerImpl final {
private:
    // This can be run in multiple threads if needed.
    void HandleRpcCalls() {

        int policyType = configMap["CACHE_REPLACEMENT_TYPE"];
        if (policyType == 1) {
            INFO("KVServer", "LRU Policy Selected");
            LRUCache *lruCache = new LRUCache(configMap["CACHE_SIZE"]);
            new GetCallData(&asyncService, completionQueue.get(), lruCache);
            new DelCallData(&asyncService, completionQueue.get(), lruCache);
            new PutCallData(&asyncService, completionQueue.get(), lruCache);
        } else {
            INFO("KVServer", "LFU Policy Selected");
            LFUCache *lfuCache = new LFUCache(configMap["CACHE_SIZE"]);
            new GetCallData(&asyncService, completionQueue.get(), lfuCache);
            new DelCallData(&asyncService, completionQueue.get(), lfuCache);
            new PutCallData(&asyncService, completionQueue.get(), lfuCache);
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
            GPR_ASSERT(completionQueue->Next(&tag, &ok));

            //Confirming if the fetching from the queue is successful or not
            GPR_ASSERT(ok);

            //type-casting the respective call and proceeding the next process.
            static_cast<CallData *>(tag)->Proceed();

        }
    }

    std::unique_ptr<ServerCompletionQueue> completionQueue;
    KeyValueStore::AsyncService asyncService;
    std::unique_ptr<Server> server;
    std::map<std::string, int> configMap;

public:
    ~KeyValueServerImpl() {
        server->Shutdown();
        // Always shutdown the completion queue after the server.
        completionQueue->Shutdown();
    }

    // There is no shutdown handling in this code.
    void Run() {
        FileService *fileService = new FileService();
        configMap = fileService->getConfig();
        std::string server_address("localhost:" + to_string(configMap["LISTENING_PORT"]));


        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "asyncService" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *asynchronous* service.
        builder.RegisterService(&asyncService);
        // Get hold of the completion queue used for the asynchronous communication
        // with the gRPC runtime.
        completionQueue = builder.AddCompletionQueue();
        // Finally assemble the server.
        server = builder.BuildAndStart();
        WARN("KVServer", "Server listening on "+ server_address);

        // Proceed to the server's main loop.
        HandleRpcCalls();
    }

};

int main(int argc, char **argv) {
    KeyValueServerImpl server;
    server.Run();

    return 0;
}