#include "ft_write_ee_op.h"

Napi::Object FtWriteEEOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("writeEESync", Napi::Function::New(env, FtWriteEEOp::InvokeSync));
    exports.Set("writeEE", Napi::Function::New(env, FtWriteEEOp::Invoke));
    return exports;
}

Napi::Object FtWriteEEOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    WORD value = info[2].As<Napi::Number>().Int32Value();
    FT_STATUS ftStatus = FT_WriteEE(ftHandle, wordOffset, value);
    return CreateResult(info.Env(), ftStatus);
}

Napi::Promise FtWriteEEOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    WORD value = info[2].As<Napi::Number>().Int32Value();
    auto *operation = new FtWriteEEOp(info.Env(), ftHandle, wordOffset, value);
    operation->Queue();
    return operation->Promise();
}

FtWriteEEOp::FtWriteEEOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset, WORD value)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      wordOffset(wordOffset),
      value(value)
{
}

void FtWriteEEOp::Execute()
{
    ftStatus = FT_WriteEE(ftHandle, wordOffset, value);
}

void FtWriteEEOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus));
}

Napi::Object FtWriteEEOp::CreateResult(Napi::Env env, FT_STATUS ftStatus)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    return result;
}