#include "ft_ee_ua_write_op.h"

Napi::Object FtEeUaWriteOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("eeUaWriteSync", Napi::Function::New(env, FtEeUaWriteOp::InvokeSync));
    exports.Set("eeUaWrite", Napi::Function::New(env, FtEeUaWriteOp::Invoke));
    return exports;
}

Napi::Number FtEeUaWriteOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    Napi::Buffer<unsigned char> buf = info[1].As<Napi::Buffer<unsigned char>>();
    DWORD numBytesToWrite = info[2].As<Napi::Number>().Uint32Value();
    if (numBytesToWrite > buf.ByteLength())
    {
        numBytesToWrite = buf.ByteLength();
    }
    unsigned char *uaBuffer = buf.Data();
    FT_STATUS ftStatus = FT_EE_UAWrite(ftHandle, uaBuffer, numBytesToWrite);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtEeUaWriteOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    Napi::Buffer<unsigned char> buf = info[1].As<Napi::Buffer<unsigned char>>();
    DWORD numBytesToWrite = info[2].As<Napi::Number>().Uint32Value();
    if (numBytesToWrite > buf.ByteLength())
    {
        numBytesToWrite = buf.ByteLength();
    }
    auto *operation = new FtEeUaWriteOp(info.Env(), ftHandle, buf, numBytesToWrite);
    operation->Queue();
    return operation->Promise();
}

FtEeUaWriteOp::FtEeUaWriteOp(Napi::Env env, FT_HANDLE ftHandle, Napi::Buffer<unsigned char> &buffer, DWORD numBytesToWrite)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      numBytesToWrite(numBytesToWrite),
      objRef(Napi::Persistent(buffer))
{
    uaBuffer = buffer.Data();
}

void FtEeUaWriteOp::Execute()
{
    ftStatus = FT_EE_UAWrite(ftHandle, uaBuffer, numBytesToWrite);
}

void FtEeUaWriteOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}