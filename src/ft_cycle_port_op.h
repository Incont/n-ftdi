#ifndef FT_CYCLE_PORT_H_
#define FT_CYCLE_PORT_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtCyclePortOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtCyclePortOp(Napi::Env env, FT_HANDLE ftHandle);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
};

#endif // FT_CYCLE_PORT_H_