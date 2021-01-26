#ifndef FT_SET_LATENCY_TIMER_OP_H_
#define FT_SET_LATENCY_TIMER_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtSetLatencyTimerOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtSetLatencyTimerOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR latency);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    UCHAR latency;
};

#endif // FT_SET_LATENCY_TIMER_OP_H_