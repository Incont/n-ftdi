#include "ft_create_device_info_list_op.h"

Napi::Object FtCreateDeviceInfoListOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("createDeviceInfoListSync", Napi::Function::New(env, FtCreateDeviceInfoListOp::InvokeSync));
    exports.Set("createDeviceInfoList", Napi::Function::New(env, FtCreateDeviceInfoListOp::Invoke));
    return exports;
}

Napi::Object FtCreateDeviceInfoListOp::InvokeSync(const Napi::CallbackInfo &info)
{
    DWORD devCount;
    FT_STATUS ftStatus = FT_CreateDeviceInfoList(&devCount);
    return CreateResult(info.Env(), ftStatus, devCount);
}

Napi::Promise FtCreateDeviceInfoListOp::Invoke(const Napi::CallbackInfo &info)
{
    auto *operation = new FtCreateDeviceInfoListOp(info.Env());
    operation->Queue();
    return operation->Promise();
}

FtCreateDeviceInfoListOp::FtCreateDeviceInfoListOp(Napi::Env env) : FtBaseOp(env) {}

void FtCreateDeviceInfoListOp::Execute()
{
    ftStatus = FT_CreateDeviceInfoList(&devCount);
}

void FtCreateDeviceInfoListOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, devCount));
}

Napi::Object FtCreateDeviceInfoListOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("devCount", devCount);
    return result;
}