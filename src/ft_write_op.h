#ifndef FT_WRITE_H_
#define FT_WRITE_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtWriteOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtWriteOp(Napi::Env env, FT_HANDLE ftHandle, Napi::Buffer<char> &buffer, DWORD numBytesToWrite);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    DWORD numBytesToWrite;
    Napi::Reference<Napi::Buffer<char>> objRef;
    void *txBuffer;
    DWORD numBytesWritten;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD numBytesWritten);
};

#endif // FT_WRITE_H_
