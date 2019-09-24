#ifndef FT_READ_H_
#define FT_READ_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtReadOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtReadOp(Napi::Env env, FT_HANDLE ftHandle, Napi::ArrayBuffer& buffer, DWORD numBytesToRead);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD numBytesToRead;
    Napi::Reference<Napi::ArrayBuffer> objRef;
    char* rxBuffer;
    DWORD numBytesRead;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, Napi::ArrayBuffer rxBuffer, DWORD numBytesRead);
};

#endif // FT_READ_H_
