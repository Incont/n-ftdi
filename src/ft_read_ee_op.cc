#include "ft_read_ee_op.h"

Napi::Object FtReadEeOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("readEESync", Napi::Function::New(env, FtReadEeOp::InvokeSync));
    exports.Set("readEE", Napi::Function::New(env, FtReadEeOp::Invoke));
    return exports;
}

Napi::Object FtReadEeOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    WORD value;
    FT_STATUS ftStatus = FT_ReadEE(ftHandle, wordOffset, &value);
    return CreateResult(info.Env(), ftStatus, value);
}

Napi::Promise FtReadEeOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD wordOffset = info[1].As<Napi::Number>().Uint32Value();
    auto *operation = new FtReadEeOp(info.Env(), ftHandle, wordOffset);
    operation->Queue();
    return operation->Promise();
}

FtReadEeOp::FtReadEeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      wordOffset(wordOffset)
{
}

void FtReadEeOp::Execute()
{
    ftStatus = FT_ReadEE(ftHandle, wordOffset, &value);
}

void FtReadEeOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, value));
}

Napi::Object FtReadEeOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, WORD value)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("value", value);
    return result;
}