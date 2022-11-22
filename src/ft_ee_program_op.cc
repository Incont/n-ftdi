#include "ft_ee_program_op.h"

Napi::Object FtEeProgramOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("eeProgramSync", Napi::Function::New(env, FtEeProgramOp::InvokeSync));
    exports.Set("eeProgram", Napi::Function::New(env, FtEeProgramOp::Invoke));
    return exports;
}

Napi::Number FtEeProgramOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    PFT_PROGRAM_DATA pftData = FtProgramDataWrapper::GetData(info[1]);
    FT_STATUS ftStatus = FT_EE_Program(ftHandle, pftData);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtEeProgramOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    auto *operation = new FtEeProgramOp(info.Env(), ftHandle, FtProgramDataWrapper::Unwrap(info[1].As<Napi::Object>()));
    operation->Queue();
    return operation->Promise();
}

FtEeProgramOp::FtEeProgramOp(Napi::Env env, FT_HANDLE ftHandle, FtProgramDataWrapper *pftProgramDataWrapper) : FtBaseOp(env), ftHandle(ftHandle), pftProgramDataWrapper(pftProgramDataWrapper)
{
    pftProgramDataWrapper->Ref();
}

void FtEeProgramOp::Execute()
{
    ftStatus = FT_EE_Program(ftHandle, pftProgramDataWrapper->GetData());
}

void FtEeProgramOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

void FtEeProgramOp::Destroy()
{
    pftProgramDataWrapper->Unref();
}
