#ifndef FT_READ_EE_H_
#define FT_READ_EE_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtReadEeOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtReadEeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD wordOffset;
    WORD value;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, WORD value);
};

#endif // FT_READ_EE_H_