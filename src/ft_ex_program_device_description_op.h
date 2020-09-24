#ifndef FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_
#define FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtExProgrammDeviceDescriptionOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtExProgrammDeviceDescriptionOp(Napi::Env env, FT_HANDLE ftHandle, std::string description);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    char description[64];
    inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus);
};

#endif // FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_