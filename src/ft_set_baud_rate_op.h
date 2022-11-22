#ifndef FT_SET_BAUD_RATE_OP_H_
#define FT_SET_BAUD_RATE_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtSetBaudRateOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtSetBaudRateOp(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    ULONG baudRate;
};

#endif // FT_SET_BAUD_RATE_OP_H_