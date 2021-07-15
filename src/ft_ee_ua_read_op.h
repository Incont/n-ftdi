#ifndef FT_EE_UA_READ_OP_H_
#define FT_EE_UA_READ_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtEeUaReadOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtEeUaReadOp(Napi::Env env, FT_HANDLE ftHandle, Napi::Buffer<unsigned char> &uaBuffer, DWORD numBytesToRead);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD numBytesToRead;
    Napi::Reference<Napi::Buffer<unsigned char>> objRef;
    unsigned char *uaBuffer;
    DWORD numBytesRead;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, Napi::Buffer<unsigned char> uaBuffer, DWORD numBytesRead);
};

#endif // FT_EE_UA_READ_OP_H_