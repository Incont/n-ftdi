#include "ft_get_device_info_detail_op.h"

Napi::Object FtGetDeviceInfoDetailOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getDeviceInfoDetailSync", Napi::Function::New(env, FtGetDeviceInfoDetailOp::InvokeSync));
    exports.Set("getDeviceInfoDetail", Napi::Function::New(env, FtGetDeviceInfoDetailOp::Invoke));
    return exports;
}

Napi::Object FtGetDeviceInfoDetailOp::InvokeSync(const Napi::CallbackInfo &info)
{
    DWORD index = info[0].As<Napi::Number>().Int32Value();
    DWORD flags;
    DWORD id;
    DWORD type;
    DWORD locId;
    char serialNumber[16];
    char description[64];
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
    return CreateResult(info.Env(), ftStatus, flags, id, type, locId, serialNumber, description, ftHandle);
}

Napi::Promise FtGetDeviceInfoDetailOp::Invoke(const Napi::CallbackInfo &info)
{
    DWORD index = info[0].As<Napi::Number>().Int32Value();
    auto *operation = new FtGetDeviceInfoDetailOp(info.Env(), index);
    operation->Queue();
    return operation->Promise();
}

FtGetDeviceInfoDetailOp::FtGetDeviceInfoDetailOp(Napi::Env env, DWORD index) : FtBaseOp(env), index(index) {}

void FtGetDeviceInfoDetailOp::Execute()
{
    ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
}

void FtGetDeviceInfoDetailOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, flags, id, type, locId, serialNumber, description, ftHandle));
}

Napi::Object FtGetDeviceInfoDetailOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    DWORD flags,
    DWORD id,
    DWORD type,
    DWORD locId,
    char *serialNumber,
    char *description,
    FT_HANDLE ftHandle)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    Napi::Object deviceInfoNode = Napi::Object::New(env);
    Napi::Value nFtHandler = ftHandle == nullptr
                                 ? env.Null()
                                 : FtHandlerWrapper::NewInstance(env, ftHandle);
    deviceInfoNode.Set("flags", flags);
    deviceInfoNode.Set("type", type);
    deviceInfoNode.Set("id", id);
    deviceInfoNode.Set("locId", locId);
    deviceInfoNode.Set("serialNumber", serialNumber);
    deviceInfoNode.Set("description", description);
    deviceInfoNode.Set("ftHandle", nFtHandler);
    result.Set("deviceInfoNode", deviceInfoNode);
    return result;
}