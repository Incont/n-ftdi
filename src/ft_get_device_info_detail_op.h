#ifndef FT_GET_DEVICE_INFO_DETAIL_OP_H_
#define FT_GET_DEVICE_INFO_DETAIL_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtGetDeviceInfoDetailOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtGetDeviceInfoDetailOp(Napi::Env env, DWORD index);
    void Execute() override;
    void OnOK() override;

private:
    DWORD index;
    DWORD flags;
    DWORD id;
    DWORD type;
    DWORD locId;
    char serialNumber[16];
    char description[64];
    FT_HANDLE ftHandle;
    inline static Napi::Object CreateResult(
        Napi::Env env,
        FT_STATUS ftStatus,
        DWORD flags,
        DWORD id,
        DWORD type,
        DWORD locId,
        char *serialNumber,
        char *description,
        FT_HANDLE ftHandle);
};

#endif // FT_GET_DEVICE_INFO_DETAIL_OP_H_