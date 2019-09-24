#include "ft_get_status_op.h"

Napi::Object FtGetStatusOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getStatusSync", Napi::Function::New(env, FtGetStatusOp::InvokeSync));
    exports.Set("getStatus", Napi::Function::New(env, FtGetStatusOp::Invoke));
    return exports;
}

Napi::Object FtGetStatusOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD rxQueue;
    DWORD txQueue;
    DWORD eventStatus;
    FT_STATUS ftStatus = FT_GetStatus(ftHandle, &rxQueue, &txQueue, &eventStatus);
    return CreateResult(info.Env(), ftStatus, rxQueue, txQueue, eventStatus);
}

Napi::Promise FtGetStatusOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    auto *operation = new FtGetStatusOp(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtGetStatusOp::FtGetStatusOp(Napi::Env env, FT_HANDLE ftHandle) : FtBaseOp(env), ftHandle(ftHandle) {}

void FtGetStatusOp::Execute()
{
    ftStatus = FT_GetStatus(ftHandle, &rxQueue, &txQueue, &eventStatus);
}

void FtGetStatusOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, rxQueue, txQueue, eventStatus));
}

Napi::Object FtGetStatusOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD rxQueue, DWORD txQueue, DWORD eventStatus)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("rxQueue", rxQueue);
    result.Set("txQueue", txQueue);
    result.Set("eventStatus", eventStatus);
    return result;
}