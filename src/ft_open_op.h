#ifndef FT_OPEN_OP_H_
#define FT_OPEN_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtOpenOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtOpenOp(Napi::Env env, DWORD index);
    void Execute();
    void OnOK();

private:
    DWORD index;
    FT_HANDLE ftHandle;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

#endif // FT_OPEN_OP_H_