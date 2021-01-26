#include "ft_purge_op.h"

Napi::Object FtPurgeOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setPurgeSunc", Napi::Function::New(env, FtPurgeOp::InvokeSync));
    exports.Set("setPurge", Napi::Function::New(env, FtPurgeOp::Invoke));
    return exports;
}

Napi::Number FtPurgeOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD mask = info[1].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_Purge(ftHandle, mask);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtPurgeOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD mask = info[1].As<Napi::Number>().Uint32Value();
    auto *operation = new FtPurgeOp(info.Env(), ftHandle, mask);
    operation->Queue();
    return operation->Promise();
}

FtPurgeOp::FtPurgeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD mask)
    : FtBaseOp(env), ftHandle(ftHandle), mask(mask) {}

void FtPurgeOp::Execute()
{
    ftStatus = FT_Purge(ftHandle, mask);
}

void FtPurgeOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}