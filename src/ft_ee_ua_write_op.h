#ifndef FT_EE_UA_WRITE_H_
#define FT_EE_UA_WRITE_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtEeUaWriteOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtEeUaWriteOp(Napi::Env env, FT_HANDLE ftHandle, Napi::Buffer<unsigned char> &buffer, DWORD numBytesToWrite);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    DWORD numBytesToWrite;
    Napi::Reference<Napi::Buffer<unsigned char>> objRef;
    unsigned char *uaBuffer;
};

#endif // FT_EE_UA_WRITE_H_