#include "ft_handler_wrapper.h"

Napi::FunctionReference FtHandlerWrapper::constructor;

Napi::Object FtHandlerWrapper::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(
        env,
        "FtHandler",
        {InstanceMethod("free", &FtHandlerWrapper::Free)});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FtHandler", func);
    return exports;
}

Napi::Object FtHandlerWrapper::NewInstance(Napi::Env env, FT_HANDLE ftHandle)
{
    Napi::EscapableHandleScope scope(env);
    Napi::Object obj = constructor.New({});
    FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(obj);
    wrapper->ftHandle = ftHandle;
    return scope.Escape(napi_value(obj)).ToObject();
}

FT_HANDLE FtHandlerWrapper::GetFtHandler(Napi::Value value)
{
    FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(value.As<Napi::Object>());
    return wrapper->GetFtHandler();
}

FtHandlerWrapper::FtHandlerWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<FtHandlerWrapper>(info) {}

void FtHandlerWrapper::Free(const Napi::CallbackInfo &info)
{
    this->ftHandle = nullptr;
}

FtHandlerWrapper::~FtHandlerWrapper()
{
    if (this->ftHandle != nullptr)
        FT_Close(this->ftHandle);
}

FT_HANDLE FtHandlerWrapper::GetFtHandler()
{
    return ftHandle;
}