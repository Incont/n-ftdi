#include "ft_set_bit_mode_op.h"

Napi::Object FtSetBitModeOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setBitModeSync", Napi::Function::New(env, FtSetBitModeOp::InvokeSync));
    exports.Set("setBitMode", Napi::Function::New(env, FtSetBitModeOp::Invoke));
    return exports;
}

Napi::Number FtSetBitModeOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    UCHAR mask = info[1].As<Napi::Number>().Uint32Value();
    UCHAR bitMode = info[2].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetBitMode(ftHandle, mask, bitMode);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetBitModeOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    UCHAR mask = info[1].As<Napi::Number>().Uint32Value();
    UCHAR bitMode = info[2].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetBitModeOp(info.Env(), ftHandle, mask, bitMode);
    operation->Queue();
    return operation->Promise();
}

FtSetBitModeOp::FtSetBitModeOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR mask, UCHAR bitMode)
    : FtBaseOp(env), ftHandle(ftHandle), mask(mask), bitMode(bitMode) {}

void FtSetBitModeOp::Execute()
{
    ftStatus = FT_SetBitMode(ftHandle, mask, bitMode);
}

void FtSetBitModeOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}