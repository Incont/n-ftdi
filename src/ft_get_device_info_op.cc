#include "ft_get_device_info_op.h"

Napi::Object FtGetDeviceInfoOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getDeviceInfoSync", Napi::Function::New(env, FtGetDeviceInfoOp::InvokeSync));
    exports.Set("getDeviceInfo", Napi::Function::New(env, FtGetDeviceInfoOp::Invoke));
    return exports;
}

Napi::Object FtGetDeviceInfoOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    FT_DEVICE ftDevice;
    DWORD deviceId;
    char serialNumber[16];
    char description[64];
    FT_STATUS ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceId, serialNumber, description, nullptr);
    return CreateResult(info.Env(), ftStatus, ftDevice, deviceId, serialNumber, description);
}

Napi::Promise FtGetDeviceInfoOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    auto *operation = new FtGetDeviceInfoOp(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtGetDeviceInfoOp::FtGetDeviceInfoOp(Napi::Env env, FT_HANDLE ftHandle) : FtBaseOp(env), ftHandle(ftHandle) {}

void FtGetDeviceInfoOp::Execute()
{
    ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceId, serialNumber, description, nullptr);
}

void FtGetDeviceInfoOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, ftDevice, deviceId, serialNumber, description));
}

Napi::Object FtGetDeviceInfoOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    FT_DEVICE ftDevice,
    DWORD deviceId,
    char *serialNumber,
    char *description)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("ftDevice", ftDevice);
    result.Set("deviceId", deviceId);
    result.Set("serialNumber", serialNumber);
    result.Set("description", description);
    return result;
}