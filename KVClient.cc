
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>

#include "proto/keyvalue.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Request;
using keyvaluestore::Response;

class KeyValueStoreClient {
private:
    grpc::CompletionQueue queue;
    grpc::ClientContext context;
    std::unique_ptr<KeyValueStore::Stub> stub_;


public:
    explicit KeyValueStoreClient(std::shared_ptr<Channel> channel)
            : stub_(KeyValueStore::NewStub(channel)) {}

    // Requests each key in the vector and displays the key and its corresponding
    // value as a pair

    ~KeyValueStoreClient(){
        std::cout<<"Shutting down the client....." << std::endl;
        queue.Shutdown();
    }

    void GetValues(const std::vector<std::string>& keys) {
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        Request request;
        Response response;
        Status status;

        auto stream = stub_->PrepareAsyncGetValues(&context, &queue);
        stream->StartCall(this);
        for (const auto& key : keys) {
            // Key we are sending to the server.
            request.set_key(key);
            std::cout << key << " : " << response.value() << "\n";
            stream->Write(request, this);

            // Get the value for the sent key
            stream->Read(&response, this);
        }
        stream->WritesDone(this);
        stream->Finish(&status, this);
        if (!status.ok()) {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            std::cout << "RPC failed";
        }
    }

};

int main(int argc, char** argv) {
    grpc::ChannelArguments args;
    std::vector<
    std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
            interceptor_creators;
    auto channel = grpc::experimental::CreateCustomChannelWithInterceptors(
            "localhost:8090", grpc::InsecureChannelCredentials(), args,
            std::move(interceptor_creators));
    KeyValueStoreClient client(channel);
    std::vector<std::string> keys = {"key1", "key2", "key3", "key4",
                                     "key5", "key1", "key2", "key4"};
    client.GetValues(keys);

    return 0;
}