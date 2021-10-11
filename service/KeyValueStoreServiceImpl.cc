#include <vector>

#include <grpcpp/grpcpp.h>
#include "../proto/keyvalue.grpc.pb.h"

using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Request;
using keyvaluestore::Response;

struct kv_pair {
    const char* key;
    const char* value;
};

static const kv_pair kvs_map[] = {
        {"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"},
        {"key4", "value4"}, {"key5", "value5"},
};

const char* get_value_from_map(const char* key) {
    for (size_t i = 0; i < sizeof(kvs_map) / sizeof(kv_pair); ++i) {
        if (strcmp(key, kvs_map[i].key) == 0) {
            return kvs_map[i].value;
        }
    }
    return "";
}

// Logic and data behind the server's behavior.
class KeyValueStoreServiceImpl final : public KeyValueStore::Service {
    Status GetValues(ServerContext* context,
                     ServerReaderWriter<Response, Request>* stream) override {
        Request request;
        while (stream->Read(&request)) {
            Response response;
            response.set_value(get_value_from_map(request.key().c_str()));
            stream->Write(response);
        }
        return Status::OK;
    }

    Status PutValues(ServerContext* context,
                     ServerReaderWriter<Response, Request>* stream) override {
        Request request;
        while(stream->Read(&request)){
            Response response;
            response.set_value(get_value_from_map(request.key().c_str()));
            stream->Write(response);
        }
        return Status::OK;
    }

    Status DelValue(ServerContext* context,
                    ServerReaderWriter<Response, Request>* stream) override {
        return Status::OK;
    }
};