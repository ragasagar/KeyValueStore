
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
public:
    KeyValueStoreClient(std::shared_ptr<Channel> channel)
            : stub_(KeyValueStore::NewStub(channel)) {}

    // Requests each key in the vector and displays the key and its corresponding
    // value as a pair
    void GetValues(const std::vector<std::string>& keys) {
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;
        auto stream = stub_->GetValues(&context);
        for (const auto& key : keys) {
            // Key we are sending to the server.
            Request request;
            request.set_key(key);
            stream->Write(request);

            // Get the value for the sent key
            Response response;
            stream->Read(&response);
            std::cout << key << " : " << response.value() << "\n";
        }
        stream->WritesDone();
        Status status = stream->Finish();
        if (!status.ok()) {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            std::cout << "RPC failed";
        }
    }

private:
    std::unique_ptr<KeyValueStore::Stub> stub_;
};

int main(int argc, char** argv) {
    grpc::ChannelArguments args;
    std::vector<
    std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
            interceptor_creators;
    auto channel = grpc::experimental::CreateCustomChannelWithInterceptors(
            "localhost:50051", grpc::InsecureChannelCredentials(), args,
            std::move(interceptor_creators));
    KeyValueStoreClient client(channel);
    std::vector<std::string> keys = {"key1", "key2", "key3", "key4",
                                     "key5", "key1", "key2", "key4"};
    client.GetValues(keys);

    return 0;
}