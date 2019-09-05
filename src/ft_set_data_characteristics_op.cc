#include "ft_set_data_characteristics_op.h"

Napi::Object FtSetDataCharacteristicsOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setDataCharacteristicsSync", Napi::Function::New(env, FtSetDataCharacteristicsOp::InvokeSync));
    exports.Set("setDataCharacteristics", Napi::Function::New(env, FtSetDataCharacteristicsOp::Invoke));
    return exports;
}

Napi::Number FtSetDataCharacteristicsOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
    UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
    UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetDataCharacteristicsOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
    UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
    UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetDataCharacteristicsOp(info.Env(), ftHandle, wordLength, stopBits, parity);
    operation->Queue();
    return operation->Promise();
}

FtSetDataCharacteristicsOp::FtSetDataCharacteristicsOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR wordLength, UCHAR stopBits, UCHAR parity)
    : FtBaseOp(env), ftHandle(ftHandle), wordLength(wordLength), stopBits(stopBits), parity(parity) {}

void FtSetDataCharacteristicsOp::Execute()
{
    ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
}

void FtSetDataCharacteristicsOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}