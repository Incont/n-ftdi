#ifndef FT_WRITE_EE_H_
#define FT_WRITE_EE_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtWriteEEOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtWriteEEOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset, WORD value);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD wordOffset;
    WORD value;
};

#endif // FT_WRITE_EE_H_