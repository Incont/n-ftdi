#include "ft_get_queue_status_op.h"

Napi::Object FtGetQueueStatusOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getQueueStatusSync", Napi::Function::New(env, FtGetQueueStatusOp::InvokeSync));
    exports.Set("getQueueStatus", Napi::Function::New(env, FtGetQueueStatusOp::Invoke));
    return exports;
}

Napi::Object FtGetQueueStatusOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    DWORD rxQueue;
    FT_STATUS ftStatus = FT_GetQueueStatus(ftHandle, &rxQueue);
    return CreateResult(info.Env(), ftStatus, rxQueue);
}

Napi::Promise FtGetQueueStatusOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    auto *operation = new FtGetQueueStatusOp(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtGetQueueStatusOp::FtGetQueueStatusOp(Napi::Env env, FT_HANDLE ftHandle) : FtBaseOp(env), ftHandle(ftHandle) {}

void FtGetQueueStatusOp::Execute()
{
    ftStatus = FT_GetQueueStatus(ftHandle, &rxQueue);
}

void FtGetQueueStatusOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, rxQueue));
}

Napi::Object FtGetQueueStatusOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD rxQueue)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("rxQueue", rxQueue);
    return result;
}