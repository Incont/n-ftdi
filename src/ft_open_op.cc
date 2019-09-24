#include "ft_open_op.h"

Napi::Object FtOpenOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("openSync", Napi::Function::New(env, FtOpenOp::InvokeSync));
    exports.Set("open", Napi::Function::New(env, FtOpenOp::Invoke));
    return exports;
}

Napi::Object FtOpenOp::InvokeSync(const Napi::CallbackInfo &info)
{
    DWORD index = info[0].As<Napi::Number>().Int32Value();
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus = FT_Open(index, &ftHandle);
    return CreateResult(info.Env(), ftStatus, ftHandle);
}

Napi::Promise FtOpenOp::Invoke(const Napi::CallbackInfo &info)
{
    DWORD index = info[0].As<Napi::Number>().Int32Value();
    auto *operation = new FtOpenOp(info.Env(), index);
    operation->Queue();
    return operation->Promise();
}

FtOpenOp::FtOpenOp(Napi::Env env, DWORD index) : FtBaseOp(env), index(index) {}

void FtOpenOp::Execute()
{
    ftStatus = FT_Open(index, &ftHandle);
}

void FtOpenOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object FtOpenOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    if(ftHandle != nullptr)
    {
        result.Set("ftHandle", Napi::External<void>::New(env, ftHandle));
    }
    return result;
}