#ifndef FT_OPEN_EX_OP_H_
#define FT_OPEN_EX_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtOpenExOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtOpenExOp(Napi::Env env, PVOID pvArg1, DWORD flags);
    void Execute();
    void OnOK();

private:
    PVOID pvArg1;
    DWORD flags;
    FT_HANDLE ftHandle;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

#endif // FT_OPEN_EX_OP_H_