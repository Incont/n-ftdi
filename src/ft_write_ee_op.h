#ifndef FT_WRITE_EE_OP_H_
#define FT_WRITE_EE_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtWriteEeOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtWriteEeOp(Napi::Env env, FT_HANDLE ftHandle, DWORD wordOffset, WORD value);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD wordOffset;
    WORD value;
};

#endif // FT_WRITE_EE_OP_H_