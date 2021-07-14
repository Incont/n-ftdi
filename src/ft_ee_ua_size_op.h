#ifndef FT_EE_UA_SIZE_OP_H_
#define FT_EE_UA_SIZE_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtEeUaSize : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtEeUaSize(Napi::Env env, FT_HANDLE ftHandle);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD uaSize;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD uaSize);
};

#endif // FT_EE_UA_SIZE_OP_H_