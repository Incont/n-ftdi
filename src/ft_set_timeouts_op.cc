#include "ft_set_timeouts_op.h"

Napi::Object FtSetTimeoutsOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setTimeoutsSync", Napi::Function::New(env, FtSetTimeoutsOp::InvokeSync));
    exports.Set("setTimeouts", Napi::Function::New(env, FtSetTimeoutsOp::Invoke));
    return exports;
}

Napi::Number FtSetTimeoutsOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD readTimeout = info[1].As<Napi::Number>().Uint32Value();
    DWORD writeTimeout = info[2].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetTimeouts(ftHandle, readTimeout, writeTimeout);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetTimeoutsOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD readTimeout = info[1].As<Napi::Number>().Uint32Value();
    DWORD writeTimeout = info[2].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetTimeoutsOp(info.Env(), ftHandle, readTimeout, writeTimeout);
    operation->Queue();
    return operation->Promise();
}

FtSetTimeoutsOp::FtSetTimeoutsOp(Napi::Env env, FT_HANDLE ftHandle, DWORD readTimeout, DWORD writeTimeout)
    : FtBaseOp(env), ftHandle(ftHandle), readTimeout(readTimeout), writeTimeout(writeTimeout) {}

void FtSetTimeoutsOp::Execute()
{
    ftStatus = FT_SetTimeouts(ftHandle, readTimeout, writeTimeout);
}

void FtSetTimeoutsOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}