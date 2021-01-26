#include "ft_set_latency_timer_op.h"

Napi::Object FtSetLatencyTimerOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setLatencyTimerSync", Napi::Function::New(env, FtSetLatencyTimerOp::InvokeSync));
    exports.Set("setLatencyTimer", Napi::Function::New(env, FtSetLatencyTimerOp::Invoke));
    return exports;
}

Napi::Number FtSetLatencyTimerOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    UCHAR latency = info[1].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetLatencyTimer(ftHandle, latency);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetLatencyTimerOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    UCHAR latency = info[1].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetLatencyTimerOp(info.Env(), ftHandle, latency);
    operation->Queue();
    return operation->Promise();
}

FtSetLatencyTimerOp::FtSetLatencyTimerOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR latency)
    : FtBaseOp(env), ftHandle(ftHandle), latency(latency) {}

void FtSetLatencyTimerOp::Execute()
{
    ftStatus = FT_SetLatencyTimer(ftHandle, latency);
}

void FtSetLatencyTimerOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}