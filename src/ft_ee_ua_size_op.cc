#include "ft_ee_ua_size_op.h"

Napi::Object FtEeUaSize::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("eeUaSizeSync", Napi::Function::New(env, FtEeUaSize::InvokeSync));
    exports.Set("eeUaSize", Napi::Function::New(env, FtEeUaSize::Invoke));
    return exports;
}

Napi::Object FtEeUaSize::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    DWORD uaSize;
    FT_STATUS ftStatus = FT_EE_UASize(ftHandle, &uaSize);
    return CreateResult(info.Env(), ftStatus, uaSize);
}

Napi::Promise FtEeUaSize::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    auto *operation = new FtEeUaSize(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtEeUaSize::FtEeUaSize(Napi::Env env, FT_HANDLE ftHandle)
    : FtBaseOp(env),
      ftHandle(ftHandle)
{
}

void FtEeUaSize::Execute()
{
    ftStatus = FT_EE_UASize(ftHandle, &uaSize);
}

void FtEeUaSize::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, uaSize));
}

Napi::Object FtEeUaSize::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD uaSize)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("value", uaSize);
    return result;
}