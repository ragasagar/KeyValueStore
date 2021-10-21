
#include <iostream>
#include <memory>
#include <string>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "proto/keyvalue.grpc.pb.h"
#include "KVStorage.hpp"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Response;
using keyvaluestore::Request;

class KeyValueClient {
public:
    explicit KeyValueClient(std::shared_ptr<Channel> channel)
            : stub_(KeyValueStore::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string GetValue(const std::string &user) {
        // Data we are sending to the server.
        Request request;
        request.set_key(user);
        request.set_type(1);

        // Container for the data we expect from the server.
        Response reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The producer-consumer queue we use to communicate asynchronously with the
        // gRPC runtime.
        CompletionQueue cq;

        // Storage for the status of the RPC upon completion.
        Status status;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        std::unique_ptr<ClientAsyncResponseReader<Response> > rpc(
                stub_->PrepareAsyncGetValues(&context, request, &cq));

        // StartCall initiates the RPC call
        rpc->StartCall();

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the integer 1.
        rpc->Finish(&reply, &status, (void *) 1);
        void *got_tag;
        bool ok = false;
        // Block until the next result is available in the completion queue "cq".
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the cq_ is shutting down.
        GPR_ASSERT(cq.Next(&got_tag, &ok));

        // Verify that the result from "cq" corresponds, by its tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // ... and that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Act upon the status of the actual RPC.
        if (status.ok()) {
            return reply.value();
        } else {
            return "RPC failed";
        }
    }

    std::string PutValue(const std::string &key, const std::string &value) {
        // Data we are sending to the server.
        Request request;
        request.set_key(key);
        request.set_value(value);
        request.set_type(2);

        // Container for the data we expect from the server.
        Response reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The producer-consumer queue we use to communicate asynchronously with the
        // gRPC runtime.
        CompletionQueue cq;

        // Storage for the status of the RPC upon completion.
        Status status;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        std::unique_ptr<ClientAsyncResponseReader<Response> > rpc(
                stub_->PrepareAsyncPutValues(&context, request, &cq));

        // StartCall initiates the RPC call
        rpc->StartCall();

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the integer 1.
        rpc->Finish(&reply, &status, (void *) 1);
        void *got_tag;
        bool ok = false;
        // Block until the next result is available in the completion queue "cq".
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the cq_ is shutting down.
        GPR_ASSERT(cq.Next(&got_tag, &ok));

        // Verify that the result from "cq" corresponds, by its tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // ... and that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Act upon the status of the actual RPC.
        if (status.ok()) {
            return reply.value();
        } else {
            return "RPC failed";
        }
    }

    std::string DelValue(const std::string &user) {
        // Data we are sending to the server.
        Request request;
        request.set_key(user);
        request.set_type(3);

        // Container for the data we expect from the server.
        Response reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The producer-consumer queue we use to communicate asynchronously with the
        // gRPC runtime.
        CompletionQueue cq;

        // Storage for the status of the RPC upon completion.
        Status status;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        std::unique_ptr<ClientAsyncResponseReader<Response> > rpc(
                stub_->PrepareAsyncDelValue(&context, request, &cq));

        // StartCall initiates the RPC call
        rpc->StartCall();

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the integer 1.
        rpc->Finish(&reply, &status, (void *) 1);
        void *got_tag;
        bool ok = false;
        // Block until the next result is available in the completion queue "cq".
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the cq_ is shutting down.
        GPR_ASSERT(cq.Next(&got_tag, &ok));

        // Verify that the result from "cq" corresponds, by its tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // ... and that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Act upon the status of the actual RPC.
        if (status.ok()) {
            return reply.value();
        } else {
            return "RPC failed";
        }
    }

private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<KeyValueStore::Stub> stub_;
};

int main(int argc, char **argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    KeyValueClient keyValueClient(grpc::CreateChannel(
            "localhost:8081", grpc::InsecureChannelCredentials()));
    FileService *fileService = new FileService();
    std::vector<std::vector<std::string>> vector = fileService->getClientConfig();
    for(const auto v : vector){
        std::string arg = v.at(0);
        std::string arg2;
        std::string arg1;
        if(v.size()==2)
            arg1 = v.at(1);
        else if(v.size()==3)
        {
             arg1 = v.at(1);
             arg2 = v.at(2);
        }
        if (arg == "GET") {
            std::string reply = keyValueClient.GetValue(arg1);  // The actual RPC call!
            std::cout << "\n";
            std::cout << "KeyValueStore received GET: " << reply << std::endl;
        } else if (arg == "PUT") {
            std::string value = argv[3];
            std::string put = keyValueClient.PutValue(arg1, arg2);  // The actual RPC call!
            std::cout << "\n";
            std::cout << "KeyValueStore received PUT: " << put << std::endl;
        } else if (arg == "DEL") {
            std::string del = keyValueClient.DelValue(arg1);  // The actual RPC call!
            std::cout << "\n";
            std::cout << "KeyValueStore received DEL: " << del << std::endl;
        }
    }
//
//    std::string key = argv[2];
//    std::string arg = argv[1];

    return 0;
}