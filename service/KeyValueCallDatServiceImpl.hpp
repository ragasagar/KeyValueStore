#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "../proto/keyvalue.grpc.pb.h"
#include "../kvcache/LRUCache.hpp"

// Class encompasing the state and logic needed to serve a request.
//Base class which defines the proceed method.
class CallData {
public:
    virtual void Proceed() = 0;
};


enum CallStatus {
    CREATE, PROCESS, FINISH
};

class GetCallData final : public CallData {
public:
    // Take in the "service" instance (in this case representing an asynchronous
    // server) and the completion queue "cq" used for asynchronous communication
    // with the gRPC runtime.
    GetCallData(keyvaluestore::KeyValueStore::AsyncService *service, grpc::ServerCompletionQueue *cq, LRUCache *lruCache)
            : asyncService(service), completionQueue(cq), responseEntity(&serverContext), status_(CREATE),
              lruCache(lruCache) {
        // Invoke the serving logic right away.
        Proceed();
    }

    void Proceed() override {
        if (status_ == CREATE) {
            // Make this instance progress to the PROCESS state.
            status_ = PROCESS;

            // As part of the initial CREATE state, we *request* that the system
            // start processing GetValue requests. In this request, "this" acts are
            // the tag uniquely identifying the request (so that different CallData
            // instances can serve different requests concurrently), in this case
            // the memory address of this CallData instance.
            asyncService->RequestGetValues(&serverContext, &request, &responseEntity, completionQueue,
                                           completionQueue,
                                           this);
        } else if (status_ == PROCESS) {
            // Spawn a new CallData instance to serve new clients while we process
            // the one for this CallData. The instance will deallocate itself as
            // part of its FINISH state.
            new GetCallData(asyncService, completionQueue, lruCache);
            // The actual processing.
            std::string val = lruCache->get(request.key());
            response.set_value(val);

            // And we are done! Let the gRPC runtime know we've finished, using the
            // memory address of this instance as the uniquely identifying tag for
            // the event.
            status_ = FINISH;
            responseEntity.Finish(response, grpc::Status::OK, this);
        } else {
            GPR_ASSERT(status_ == FINISH);
            // Once in the FINISH state, deallocate ourselves (CallData).
            delete this;
        }
    }

private:
    keyvaluestore::KeyValueStore::AsyncService *asyncService;
    LRUCache *lruCache;
    grpc::ServerCompletionQueue *completionQueue;
    grpc::ServerContext serverContext;
    keyvaluestore::Request request;
    keyvaluestore::Response response;
    grpc::ServerAsyncResponseWriter<keyvaluestore::Response> responseEntity;
    CallStatus status_;  // The current serving state.
};


class PutCallData final : public CallData {
public:
    // Take in the "service" instance (in this case representing an asynchronous
    // server) and the completion queue "cq" used for asynchronous communication
    // with the gRPC runtime.
    PutCallData(keyvaluestore::KeyValueStore::AsyncService *service, grpc::ServerCompletionQueue *cq, LRUCache *lruCache)
            : asyncService(service), completionQueue(cq), responseEntity(&serverContext), status_(CREATE),
              lruCache(lruCache) {
        // Invoke the serving logic right away.
        Proceed();
    }

    void Proceed() override {
        if (status_ == CREATE) {
            // Make this instance progress to the PROCESS state.
            status_ = PROCESS;

            // As part of the initial CREATE state, we *request* that the system
            // start processing GetValue requests. In this request, "this" acts are
            // the tag uniquely identifying the request (so that different CallData
            // instances can serve different requests concurrently), in this case
            // the memory address of this CallData instance.
            asyncService->RequestPutValues(&serverContext, &request, &responseEntity, completionQueue,
                                           completionQueue,
                                           this);
        } else if (status_ == PROCESS) {
            // Spawn a new CallData instance to serve new clients while we process
            // the one for this CallData. The instance will deallocate itself as
            // part of its FINISH state.
            new PutCallData(asyncService, completionQueue, lruCache);
            // The actual processing.
            lruCache->put(request.key(), request.value());
            response.set_value(request.value());

            // And we are done! Let the gRPC runtime know we've finished, using the
            // memory address of this instance as the uniquely identifying tag for
            // the event.
            status_ = FINISH;
            responseEntity.Finish(response, grpc::Status::OK, this);
        } else {
            GPR_ASSERT(status_ == FINISH);
            // Once in the FINISH state, deallocate ourselves (CallData).
            delete this;
        }
    }

private:
    keyvaluestore::KeyValueStore::AsyncService *asyncService;
    grpc::ServerCompletionQueue *completionQueue;
    grpc::ServerContext serverContext;
    LRUCache *lruCache;
    keyvaluestore::Request request;
    keyvaluestore::Response response;
    grpc::ServerAsyncResponseWriter<keyvaluestore::Response> responseEntity;

    CallStatus status_;  // The current serving state.
};

class DelCallData final : public CallData {
public:
    // Take in the "service" instance (in this case representing an asynchronous
    // server) and the completion queue "cq" used for asynchronous communication
    // with the gRPC runtime.
    DelCallData(keyvaluestore::KeyValueStore::AsyncService *service, grpc::ServerCompletionQueue *cq, LRUCache *lruCache)
            : asyncService(service), completionQueue(cq), responseEntity(&serverContext), status_(CREATE),
              lruCache(lruCache) {
        // Invoke the serving logic right away.
        Proceed();
    }

    void Proceed() override {
        if (status_ == CREATE) {
            // Make this instance progress to the PROCESS state.
            status_ = PROCESS;

            // As part of the initial CREATE state, we *request* that the system
            // start processing GetValue requests. In this request, "this" acts are
            // the tag uniquely identifying the request (so that different CallData
            // instances can serve different requests concurrently), in this case
            // the memory address of this CallData instance.
            asyncService->RequestDelValue(&serverContext, &request, &responseEntity, completionQueue,
                                          completionQueue,
                                          this);
        } else if (status_ == PROCESS) {
            // Spawn a new CallData instance to serve new clients while we process
            // the one for this CallData. The instance will deallocate itself as
            // part of its FINISH state.
            new DelCallData(asyncService, completionQueue, lruCache);
            // The actual processing.
            std::string res = lruCache->del(request.key());
            response.set_value(res);

            // And we are done! Let the gRPC runtime know we've finished, using the
            // memory address of this instance as the uniquely identifying tag for
            // the event.
            status_ = FINISH;
            responseEntity.Finish(response, grpc::Status::OK, this);
        } else {
            GPR_ASSERT(status_ == FINISH);
            // Once in the FINISH state, deallocate ourselves (CallData).
            delete this;
        }
    }

private:
    keyvaluestore::KeyValueStore::AsyncService *asyncService;
    grpc::ServerCompletionQueue *completionQueue;
    grpc::ServerContext serverContext;
    LRUCache *lruCache;
    keyvaluestore::Request request;
    keyvaluestore::Response response;
    grpc::ServerAsyncResponseWriter<keyvaluestore::Response> responseEntity;

    CallStatus status_;  // The current serving state.
};
