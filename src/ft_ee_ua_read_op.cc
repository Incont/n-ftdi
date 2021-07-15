#include "ft_ee_ua_read_op.h"

Napi::Object FtEeUaReadOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("eeUaReadSync", Napi::Function::New(env, FtEeUaReadOp::InvokeSync));
    exports.Set("eeUaRead", Napi::Function::New(env, FtEeUaReadOp::Invoke));
    return exports;
}

Napi::Object FtEeUaReadOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    Napi::Buffer<unsigned char> buf = info[1].As<Napi::Buffer<unsigned char>>();
    DWORD numBytesToRead = info[2].As<Napi::Number>().Uint32Value();
    if (numBytesToRead > buf.ByteLength())
    {
        numBytesToRead = buf.ByteLength();
    }
    DWORD numBytesRead;
    unsigned char *uaBuffer = buf.Data();
    FT_STATUS ftStatus = FT_EE_UARead(ftHandle, uaBuffer, numBytesToRead, &numBytesRead);
    return CreateResult(info.Env(), ftStatus, buf, numBytesRead);
}

Napi::Promise FtEeUaReadOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    Napi::Buffer<unsigned char> buf = info[1].As<Napi::Buffer<unsigned char>>();
    DWORD numBytesToRead = info[2].As<Napi::Number>().Uint32Value();
    if (numBytesToRead > buf.ByteLength())
    {
        numBytesToRead = buf.ByteLength();
    }
    auto *operation = new FtEeUaReadOp(info.Env(), ftHandle, buf, numBytesToRead);
    operation->Queue();
    return operation->Promise();
}

FtEeUaReadOp::FtEeUaReadOp(Napi::Env env, FT_HANDLE ftHandle, Napi::Buffer<unsigned char> &uaBuffer, DWORD numBytesToRead)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      numBytesToRead(numBytesToRead),
      objRef(Napi::Persistent(uaBuffer))
{
    this->uaBuffer = uaBuffer.Data();
}

void FtEeUaReadOp::Execute()
{
    ftStatus = FT_EE_UARead(ftHandle, uaBuffer, numBytesToRead, &numBytesRead);
}

void FtEeUaReadOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, objRef.Value(), numBytesRead));
}

Napi::Object FtEeUaReadOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, Napi::Buffer<unsigned char> uaBuffer, DWORD numBytesRead)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("uaBuffer", uaBuffer);
    result.Set("numBytesRead", numBytesRead);
    return result;
}