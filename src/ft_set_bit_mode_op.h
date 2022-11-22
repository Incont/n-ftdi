#ifndef FT_SET_BIT_MODE_OP_H_
#define FT_SET_BIT_MODE_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtSetBitModeOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtSetBitModeOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR mask, UCHAR bitMode);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    UCHAR mask;
    UCHAR bitMode;
};

#endif // FT_SET_BIT_MODE_OP_H_