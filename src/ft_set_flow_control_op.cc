#include "ft_set_flow_control_op.h"

Napi::Object FtSetFlowControlOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setFlowControlSync", Napi::Function::New(env, FtSetFlowControlOp::InvokeSync));
    exports.Set("setFlowControl", Napi::Function::New(env, FtSetFlowControlOp::Invoke));
    return exports;
}

Napi::Number FtSetFlowControlOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
    UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
    UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
    FT_STATUS ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtSetFlowControlOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
    UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
    UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
    auto *operation = new FtSetFlowControlOp(info.Env(), ftHandle, flowControl, xon, xoff);
    operation->Queue();
    return operation->Promise();
}

FtSetFlowControlOp::FtSetFlowControlOp(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff)
    : FtBaseOp(env), ftHandle(ftHandle), flowControl(flowControl), xon(xon), xoff(xoff) {}

void FtSetFlowControlOp::Execute()
{
    ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
}

void FtSetFlowControlOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}