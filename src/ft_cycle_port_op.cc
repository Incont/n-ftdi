#include "ft_cycle_port_op.h"

Napi::Object FtCyclePortOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("cyclePortSync", Napi::Function::New(env, FtCyclePortOp::InvokeSync));
    exports.Set("cyclePort", Napi::Function::New(env, FtCyclePortOp::Invoke));
    return exports;
}

Napi::Number FtCyclePortOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    FT_STATUS ftStatus = FT_CyclePort(ftHandle);
    printf("!!!!!!\n");
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtCyclePortOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    auto *operation = new FtCyclePortOp(info.Env(), ftHandle);
    operation->Queue();
    return operation->Promise();
}

FtCyclePortOp::FtCyclePortOp(Napi::Env env, FT_HANDLE ftHandle) : FtBaseOp(env), ftHandle(ftHandle) {}

void FtCyclePortOp::Execute()
{
    ftStatus = FT_CyclePort(ftHandle);
}

void FtCyclePortOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}