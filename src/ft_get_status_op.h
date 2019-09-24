#ifndef FT_GET_STATUS_H_
#define FT_GET_STATUS_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtGetStatusOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtGetStatusOp(Napi::Env env, FT_HANDLE ftHandle);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    DWORD rxQueue;
    DWORD txQueue;
    DWORD eventStatus;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD rxQueue, DWORD txQueue, DWORD eventStatus);
};

#endif // FT_GET_STATUS_H_