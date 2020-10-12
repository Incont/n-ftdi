#include "ft_get_vid_pid_op.h"

Napi::Object FtGetVIDPIDOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getVIDPIDSync", Napi::Function::New(env, FtGetVIDPIDOp::InvokeSync));
    exports.Set("getVIDPID", Napi::Function::New(env, FtGetVIDPIDOp::Invoke));
    return exports;
}

Napi::Object FtGetVIDPIDOp::InvokeSync(const Napi::CallbackInfo &info)
{
    DWORD VID;
    DWORD PID;
    FT_STATUS ftStatus = FT_GetVIDPID(&VID, &PID);
    return CreateResult(info.Env(), ftStatus, VID, PID);
}

Napi::Promise FtGetVIDPIDOp::Invoke(const Napi::CallbackInfo &info)
{
    auto *operation = new FtGetVIDPIDOp(info.Env());
    operation->Queue();
    return operation->Promise();
}

FtGetVIDPIDOp::FtGetVIDPIDOp(Napi::Env env) : FtBaseOp(env) {}

void FtGetVIDPIDOp::Execute()
{
    ftStatus = FT_GetVIDPID(&VID, &PID);
}

void FtGetVIDPIDOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, VID, PID));
}

Napi::Object FtGetVIDPIDOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD pdwVID, DWORD pdwPID)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("pdwVID", pdwVID);
    result.Set("pdwPID", pdwPID);
    return result;
}
