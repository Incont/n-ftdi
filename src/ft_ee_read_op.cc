#include "ft_ee_read_op.h"

Napi::Object FtEeReadOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("eeReadSync", Napi::Function::New(env, FtEeReadOp::InvokeSync));
    exports.Set("eeRead", Napi::Function::New(env, FtEeReadOp::Invoke));
    return exports;
}

Napi::Number FtEeReadOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    PFT_PROGRAM_DATA pftData = FtProgramDataWrapper::GetData(info[1]);
    FT_STATUS ftStatus = FT_EE_Read(ftHandle, pftData);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtEeReadOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    PFT_PROGRAM_DATA pftData = FtProgramDataWrapper::GetData(info[1]);
    auto *operation = new FtEeReadOp(info.Env(), ftHandle, pftData);
    operation->Queue();
    return operation->Promise();
}

FtEeReadOp::FtEeReadOp(Napi::Env env, FT_HANDLE ftHandle, PFT_PROGRAM_DATA pftData) : FtBaseOp(env), ftHandle(ftHandle), pftData(pftData) {}

void FtEeReadOp::Execute()
{
    ftStatus = FT_EE_Read(ftHandle, pftData);
}

void FtEeReadOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}