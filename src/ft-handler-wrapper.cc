#include <ft-handler-wrapper.h>
#include <ftd2xx.h>

Napi::FunctionReference FtHandlerWrapper::constructor;

Napi::Object FtHandlerWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "FtHandler", {InstanceMethod("free", &FtHandlerWrapper::Free)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("FtHandler", func);
  return exports;
}

PVOID FtHandlerWrapper::GetFtHandler(Napi::Value value)
{
  FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(value.As<Napi::Object>());
  return wrapper->GetFtHandler();
}

Napi::Object FtHandlerWrapper::NewInstance(Napi::Env env, PVOID ftHandle)
{
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({});
  FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(obj);
  wrapper->_ftHandle = ftHandle;
  return scope.Escape(napi_value(obj)).ToObject();
}

FtHandlerWrapper::FtHandlerWrapper(const Napi::CallbackInfo &info) : Napi::ObjectWrap<FtHandlerWrapper>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
}

void FtHandlerWrapper::Free(const Napi::CallbackInfo &info)
{
  this->_ftHandle = nullptr;
}

FtHandlerWrapper::~FtHandlerWrapper()
{
  if(this->_ftHandle != nullptr)
    FT_Close(this->_ftHandle);
}

PVOID FtHandlerWrapper::GetFtHandler()
{
  return _ftHandle;
}