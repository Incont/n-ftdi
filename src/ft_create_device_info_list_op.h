#ifndef FT_CREATE_DEVICE_INFO_LIST_OP_H_
#define FT_CREATE_DEVICE_INFO_LIST_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtCreateDeviceInfoListOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtCreateDeviceInfoListOp(Napi::Env env);
    void Execute();
    void OnOK();

private:
    DWORD devCount;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount);
};

#endif // FT_CREATE_DEVICE_INFO_LIST_OP_H_