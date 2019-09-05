#include "ft_close_op.h"

Napi::Object FtCloseOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("closeSync", Napi::Function::New(env, FtCloseOp::InvokeSync));
    exports.Set("close", Napi::Function::New(env, FtCloseOp::Invoke));
    return exports;
}

Napi::Number FtCloseOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    FT_STATUS ftStatus = FT_Close(ftHandle);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtCloseOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    auto *operation = new FtCloseOp(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtCloseOp::FtCloseOp(Napi::Env env, FT_HANDLE ftHandle) : FtBaseOp(env), ftHandle(ftHandle) {}

void FtCloseOp::Execute()
{
    ftStatus = FT_Close(ftHandle);
}

void FtCloseOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}