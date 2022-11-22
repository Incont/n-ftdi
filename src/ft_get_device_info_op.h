#ifndef FT_GET_DEVICE_INFO_OP_H_
#define FT_GET_DEVICE_INFO_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtGetDeviceInfoOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtGetDeviceInfoOp(Napi::Env env, FT_HANDLE ftHandle);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    FT_DEVICE ftDevice;
    DWORD deviceId;
    char serialNumber[16];
    char description[64];
    inline static Napi::Object CreateResult(
        Napi::Env env,
        FT_STATUS ftStatus,
        FT_DEVICE ftDevice,
        DWORD deviceId,
        char *serialNumber,
        char *description);
};

#endif // FT_GET_DEVICE_INFO_OP_H_