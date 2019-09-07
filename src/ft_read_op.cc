#include "ft_read_op.h"

Napi::Object FtReadOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("readSync", Napi::Function::New(env, FtReadOp::InvokeSync));
    exports.Set("read", Napi::Function::New(env, FtReadOp::Invoke));
    return exports;
}

Napi::Object FtReadOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    Napi::ArrayBuffer buf = info[1].As<Napi::ArrayBuffer>();
    DWORD numBytesToRead = info[2].As<Napi::Number>().Uint32Value();
    if(numBytesToRead > buf.ByteLength()) {
        numBytesToRead = buf.ByteLength();
    }
    DWORD numBytesRead;
    void* rxBuffer = buf.Data();
    FT_STATUS ftStatus =  FT_Read(ftHandle, rxBuffer, numBytesToRead, &numBytesRead);
    return CreateResult(info.Env(), ftStatus, buf, numBytesRead);
}

Napi::Promise FtReadOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    Napi::ArrayBuffer buf = info[1].As<Napi::ArrayBuffer>();
    DWORD numBytesToRead = info[2].As<Napi::Number>().Uint32Value();
    if(numBytesToRead > buf.ByteLength()) {
        numBytesToRead = buf.ByteLength();
    }
    auto *operation = new FtReadOp(info.Env(), ftHandle, buf, numBytesToRead);
    operation->Queue();
    return operation->Promise();
}

FtReadOp::FtReadOp(Napi::Env env, FT_HANDLE ftHandle, Napi::ArrayBuffer& buffer, DWORD numBytesToRead)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      numBytesToRead(numBytesToRead),
      objRef(Napi::Persistent(buffer)) {
          rxBuffer = (char*)buffer.Data();
      }

void FtReadOp::Execute()
{
    ftStatus = FT_Read(ftHandle, rxBuffer, numBytesToRead, &numBytesRead);
}

void FtReadOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, objRef.Value(), numBytesRead));
}

Napi::Object FtReadOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, Napi::ArrayBuffer rxBuffer, DWORD numBytesRead)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("rxBuffer", rxBuffer);
    result.Set("numBytesRead", numBytesRead);
    return result;
}