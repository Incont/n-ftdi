#ifndef FT_GET_VIDPID_H_
#define FT_GET_VIDPID_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

#if _WIN32
inline FT_STATUS FT_GetVIDPID(DWORD *pdwVID, DWORD *pdwPID) { return FT_NOT_SUPPORTED; }
#endif

class FtGetVIDPIDOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtGetVIDPIDOp(Napi::Env env);
    void Execute();
    void OnOK();

private:
    DWORD VID;
    DWORD PID;
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD VID, DWORD PID);
};

#endif // FT_GET_VIDPID_H_
