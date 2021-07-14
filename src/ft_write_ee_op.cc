#include "ft_write_ee_op.h"

Napi::Object FtWriteEeOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("writeEESync", Napi::Function::New(env, FtWriteEeOp::InvokeSync));
    exports.Set("writeEE", Napi::Function::New(env, FtWriteEeOp::Invoke));
    return exports;
}

Napi::Number FtWriteEeOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    WORD value = info[2].As<Napi::Number>().Int32Value();
    FT_STATUS ftStatus = FT_WriteEE(ftHandle, wordOffset, value);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtWriteEeOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    WORD value = info[2].As<Napi::Number>().Int32Value();
    auto *operation = new FtWriteEeOp(info.Env(), ftHandle, wordOffset, value);
    operation->Queue();
    return operation->Promise();
}

FtWriteEeOp::FtWriteEeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset, WORD value)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      wordOffset(wordOffset),
      value(value)
{
}

void FtWriteEeOp::Execute()
{
    ftStatus = FT_WriteEE(ftHandle, wordOffset, value);
}

void FtWriteEeOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}