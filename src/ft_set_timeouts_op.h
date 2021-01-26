#ifndef FT_SET_TIMEOUTS_OP_H_
#define FT_SET_TIMEOUTS_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtSetTimeoutsOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtSetTimeoutsOp(Napi::Env env, FT_HANDLE ftHandle, DWORD readTimeout, DWORD writeTimeout);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD readTimeout;
    DWORD writeTimeout;
};

#endif // FT_SET_TIMEOUTS_OP_H_