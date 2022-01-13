// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: keyvalue.proto
#ifndef GRPC_keyvalue_2eproto__INCLUDED
#define GRPC_keyvalue_2eproto__INCLUDED

#include "keyvalue.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace keyvaluestore {

// A simple key-value storage service
class KeyValueStore final {
 public:
  static constexpr char const* service_full_name() {
    return "keyvaluestore.KeyValueStore";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Provides a value for each key request
    virtual ::grpc::Status GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> AsyncGetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(AsyncGetValuesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> PrepareAsyncGetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(PrepareAsyncGetValuesRaw(context, request, cq));
    }
    virtual ::grpc::Status PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> AsyncPutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(AsyncPutValuesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> PrepareAsyncPutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(PrepareAsyncPutValuesRaw(context, request, cq));
    }
    virtual ::grpc::Status DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> AsyncDelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(AsyncDelValueRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>> PrepareAsyncDelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>>(PrepareAsyncDelValueRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // Provides a value for each key request
      virtual void GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* AsyncGetValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* PrepareAsyncGetValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* AsyncPutValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* PrepareAsyncPutValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* AsyncDelValueRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::keyvaluestore::Response>* PrepareAsyncDelValueRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> AsyncGetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(AsyncGetValuesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> PrepareAsyncGetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(PrepareAsyncGetValuesRaw(context, request, cq));
    }
    ::grpc::Status PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> AsyncPutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(AsyncPutValuesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> PrepareAsyncPutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(PrepareAsyncPutValuesRaw(context, request, cq));
    }
    ::grpc::Status DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::keyvaluestore::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> AsyncDelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(AsyncDelValueRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>> PrepareAsyncDelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>>(PrepareAsyncDelValueRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) override;
      void GetValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      void PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) override;
      void PutValues(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      void DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, std::function<void(::grpc::Status)>) override;
      void DelValue(::grpc::ClientContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* AsyncGetValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* PrepareAsyncGetValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* AsyncPutValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* PrepareAsyncPutValuesRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* AsyncDelValueRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::keyvaluestore::Response>* PrepareAsyncDelValueRaw(::grpc::ClientContext* context, const ::keyvaluestore::Request& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetValues_;
    const ::grpc::internal::RpcMethod rpcmethod_PutValues_;
    const ::grpc::internal::RpcMethod rpcmethod_DelValue_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Provides a value for each key request
    virtual ::grpc::Status GetValues(::grpc::ServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response);
    virtual ::grpc::Status PutValues(::grpc::ServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response);
    virtual ::grpc::Status DelValue(::grpc::ServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetValues() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetValues(::grpc::ServerContext* context, ::keyvaluestore::Request* request, ::grpc::ServerAsyncResponseWriter< ::keyvaluestore::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_PutValues() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPutValues(::grpc::ServerContext* context, ::keyvaluestore::Request* request, ::grpc::ServerAsyncResponseWriter< ::keyvaluestore::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_DelValue() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDelValue(::grpc::ServerContext* context, ::keyvaluestore::Request* request, ::grpc::ServerAsyncResponseWriter< ::keyvaluestore::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetValues<WithAsyncMethod_PutValues<WithAsyncMethod_DelValue<Service > > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetValues() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response) { return this->GetValues(context, request, response); }));}
    void SetMessageAllocatorFor_GetValues(
        ::grpc::MessageAllocator< ::keyvaluestore::Request, ::keyvaluestore::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetValues(
      ::grpc::CallbackServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_PutValues() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response) { return this->PutValues(context, request, response); }));}
    void SetMessageAllocatorFor_PutValues(
        ::grpc::MessageAllocator< ::keyvaluestore::Request, ::keyvaluestore::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* PutValues(
      ::grpc::CallbackServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_DelValue() {
      ::grpc::Service::MarkMethodCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::keyvaluestore::Request* request, ::keyvaluestore::Response* response) { return this->DelValue(context, request, response); }));}
    void SetMessageAllocatorFor_DelValue(
        ::grpc::MessageAllocator< ::keyvaluestore::Request, ::keyvaluestore::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(2);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::keyvaluestore::Request, ::keyvaluestore::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* DelValue(
      ::grpc::CallbackServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetValues<WithCallbackMethod_PutValues<WithCallbackMethod_DelValue<Service > > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetValues() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_PutValues() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_DelValue() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetValues() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetValues(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_PutValues() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPutValues(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_DelValue() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDelValue(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetValues() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetValues(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetValues(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_PutValues() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->PutValues(context, request, response); }));
    }
    ~WithRawCallbackMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* PutValues(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_DelValue() {
      ::grpc::Service::MarkMethodRawCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->DelValue(context, request, response); }));
    }
    ~WithRawCallbackMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* DelValue(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetValues() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::keyvaluestore::Request, ::keyvaluestore::Response>* streamer) {
                       return this->StreamedGetValues(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetValues(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::keyvaluestore::Request,::keyvaluestore::Response>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_PutValues : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_PutValues() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::keyvaluestore::Request, ::keyvaluestore::Response>* streamer) {
                       return this->StreamedPutValues(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_PutValues() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status PutValues(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPutValues(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::keyvaluestore::Request,::keyvaluestore::Response>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_DelValue : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_DelValue() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler<
          ::keyvaluestore::Request, ::keyvaluestore::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::keyvaluestore::Request, ::keyvaluestore::Response>* streamer) {
                       return this->StreamedDelValue(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_DelValue() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status DelValue(::grpc::ServerContext* /*context*/, const ::keyvaluestore::Request* /*request*/, ::keyvaluestore::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedDelValue(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::keyvaluestore::Request,::keyvaluestore::Response>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetValues<WithStreamedUnaryMethod_PutValues<WithStreamedUnaryMethod_DelValue<Service > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetValues<WithStreamedUnaryMethod_PutValues<WithStreamedUnaryMethod_DelValue<Service > > > StreamedService;
};

}  // namespace keyvaluestore


#endif  // GRPC_keyvalue_2eproto__INCLUDED