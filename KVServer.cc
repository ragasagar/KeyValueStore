
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "proto/keyvalue.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Response;
using keyvaluestore::Request;

class ServerImpl final {
public:
    ~ServerImpl() {
        server->Shutdown();
        // Always shutdown the completion queue after the server.
        completionQueue->Shutdown();
    }

    // There is no shutdown handling in this code.
    void Run() {
        std::string server_address("0.0.0.0:8090");

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
        std::cout << "Server listening on " << server_address << std::endl;

        // Proceed to the server's main loop.
        HandleRpcs();
    }

private:
    // Class encompasing the state and logic needed to serve a request.
    class CallData {
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        CallData(keyvaluestore::KeyValueStore::AsyncService *service, ServerCompletionQueue *cq)
                : asyncService(service), completionQueue(cq), status_(CREATE), stream(stream){
            // Invoke the serving logic right away.
            Proceed();
        }

        void Proceed() {
            if (status_ == CREATE) {
                // Make this instance progress to the PROCESS state.
                status_ = PROCESS;

                // As part of the initial CREATE state, we *request* that the system
                // start processing SayHello requests. In this request, "this" acts are
                // the tag uniquely identifying the request (so that different CallData
                // instances can serve different requests concurrently), in this case
                // the memory address of this CallData instance.
                asyncService->RequestGetValues(&serverContext, &stream, completionQueue, completionQueue,this);
            } else if (status_ == PROCESS) {
                // Spawn a new CallData instance to serve new clients while we process
                // the one for this CallData. The instance will deallocate itself as
                // part of its FINISH state.
                new CallData(asyncService, completionQueue);

                // The actual processing.
                std::string prefix("Hello ");
                stream.Read(&request, this);

                Response response;
                response.set_value(prefix);
                stream.Write(response, this);
                // And we are done! Let the gRPC runtime know we've finished, using the
                // memory address of this instance as the uniquely identifying tag for
                // the event.
                status_ = FINISH;
                stream.Finish(Status::OK, this);
            } else {
                GPR_ASSERT(status_ == FINISH);
                // Once in the FINISH state, deallocate ourselves (CallData).
                delete this;
            }
        }

    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        keyvaluestore::KeyValueStore::AsyncService* asyncService;
        // The producer-consumer queue where for asynchronous server notifications.
        ServerCompletionQueue* completionQueue;
        // Context for the rpc, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        ServerContext serverContext;

        // What we get from the client.
        Request request;

        grpc::ServerAsyncReaderWriter<Response, Request> stream;

        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // The current serving state.
    };

    // This can be run in multiple threads if needed.
    void HandleRpcs() {
        // Spawn a new CallData instance to serve new clients.
        new CallData(&asyncService, completionQueue.get());
        void* tag;  // uniquely identifies a request.
        bool ok;
        while (true) {
            // Block waiting to read the next event from the completion queue. The
            // event is uniquely identified by its tag, which in this case is the
            // memory address of a CallData instance.
            // The return value of Next should always be checked. This return value
            // tells us whether there is any kind of event or completionQueue is shutting down.
            GPR_ASSERT(completionQueue->Next(&tag, &ok));
            GPR_ASSERT(ok);
            static_cast<CallData*>(tag)->Proceed();
        }
    }

    std::unique_ptr<ServerCompletionQueue> completionQueue;
    keyvaluestore::KeyValueStore::AsyncService asyncService;
    std::unique_ptr<Server> server;
};

int main(int argc, char** argv) {
    ServerImpl server;
    server.Run();

    return 0;
}