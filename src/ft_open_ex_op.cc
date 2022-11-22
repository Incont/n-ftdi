#include "ft_open_ex_op.h"

Napi::Object FtOpenExOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("openExSync", Napi::Function::New(env, FtOpenExOp::InvokeSync));
    exports.Set("openEx", Napi::Function::New(env, FtOpenExOp::Invoke));
    return exports;
}

Napi::Object FtOpenExOp::InvokeSync(const Napi::CallbackInfo &info)
{
    PVOID pvArg1;
    std::string snOrDsc;
    if (info[0].IsString())
    {
        snOrDsc = info[0].As<Napi::String>().Utf8Value();
        pvArg1 = (void *)snOrDsc.c_str();
    }
    else
    {
        pvArg1 = (void *)info[0].As<Napi::Number>().Int64Value();
    }
    DWORD flags = info[1].As<Napi::Number>().Int64Value();
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
    return CreateResult(info.Env(), ftStatus, ftHandle);
}

Napi::Promise FtOpenExOp::Invoke(const Napi::CallbackInfo &info)
{
    DWORD flags = info[1].As<Napi::Number>().Int64Value();
    auto *operation = new FtOpenExOp(info.Env(), info[0], flags);
    operation->Queue();
    return operation->Promise();
}

FtOpenExOp::FtOpenExOp(Napi::Env env, Napi::Value arg, DWORD flags) : FtBaseOp(env), flags(flags)
{
    if (flags == FT_OPEN_BY_LOCATION)
    {
        pvArg1 = (void *)arg.As<Napi::Number>().Int64Value();
    }
    else
    {
        std::string snOrDsc = arg.As<Napi::String>().Utf8Value();
        char *cstr = new char[snOrDsc.length() + 1];
        strcpy(cstr, snOrDsc.c_str());
        pvArg1 = cstr;
    }
}

void FtOpenExOp::Destroy()
{
    if (flags != FT_OPEN_BY_LOCATION)
    {
        delete[](char *) pvArg1;
    }
}

void FtOpenExOp::Execute()
{
    ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
}

void FtOpenExOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object FtOpenExOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    if (ftHandle != nullptr)
    {
        result.Set("ftHandle", Napi::External<void>::New(env, ftHandle));
    }
    return result;
}
