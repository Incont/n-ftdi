#ifndef FT_PURGE_OP_H_
#define FT_PURGE_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtPurgeOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtPurgeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD mask);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD mask;
};

#endif // FT_PURGE_OP_H_