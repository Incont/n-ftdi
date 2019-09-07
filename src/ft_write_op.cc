#include "ft_write_op.h"

Napi::Object FtWriteOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("writeSync", Napi::Function::New(env, FtWriteOp::InvokeSync));
    exports.Set("write", Napi::Function::New(env, FtWriteOp::Invoke));
    return exports;
}

Napi::Object FtWriteOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    Napi::ArrayBuffer buf = info[1].As<Napi::ArrayBuffer>();
    DWORD numBytesToWrite = info[2].As<Napi::Number>().Uint32Value();
    if(numBytesToWrite > buf.ByteLength()) {
        numBytesToWrite = buf.ByteLength();
    }
    DWORD numBytesWritten;
    void* txBuffer = buf.Data();
    FT_STATUS ftStatus =  FT_Write(ftHandle, txBuffer, numBytesToWrite, &numBytesWritten);
    return CreateResult(info.Env(), ftStatus, numBytesWritten);
}

Napi::Promise FtWriteOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
    Napi::ArrayBuffer buf = info[1].As<Napi::ArrayBuffer>();
    DWORD numBytesToWrite = info[2].As<Napi::Number>().Uint32Value();
    if(numBytesToWrite > buf.ByteLength()) {
        numBytesToWrite = buf.ByteLength();
    }
    auto *operation = new FtWriteOp(info.Env(), ftHandle, buf, numBytesToWrite);
    operation->Queue();
    return operation->Promise();
}

FtWriteOp::FtWriteOp(Napi::Env env, FT_HANDLE ftHandle, Napi::ArrayBuffer& buffer, DWORD numBytesToWrite)
    : FtBaseOp(env),
      ftHandle(ftHandle),
      numBytesToWrite(numBytesToWrite),
      objRef(Napi::Persistent(buffer)) {
          txBuffer = buffer.Data();
      }

void FtWriteOp::Execute()
{
    ftStatus = FT_Write(ftHandle, txBuffer, numBytesToWrite, &numBytesWritten);
}

void FtWriteOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus, numBytesWritten));
}

Napi::Object FtWriteOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD numBytesWritten)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    result.Set("numBytesWritten", numBytesWritten);
    return result;
}