#include "ft_set_baud_rate_op.h"

Napi::Object FtSetBaudRateOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setBaudRateSync", Napi::Function::New(env, FtSetBaudRateOp::InvokeSync));
    exports.Set("setBaudRate", Napi::Function::New(env, FtSetBaudRateOp::Invoke));
    return exports;
}

Napi::Number FtSetBaudRateOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetBaudRate(ftHandle, baudRate);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetBaudRateOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetBaudRateOp(info.Env(), ftHandle, baudRate);
    operation->Queue();
    return operation->Promise();
}

FtSetBaudRateOp::FtSetBaudRateOp(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate)
    : FtBaseOp(env), ftHandle(ftHandle), baudRate(baudRate) {}

void FtSetBaudRateOp::Execute()
{
    ftStatus = FT_SetBaudRate(ftHandle, baudRate);
}

void FtSetBaudRateOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}