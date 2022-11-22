#ifndef FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_
#define FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"

class FtExProgramDeviceDescriptionOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtExProgramDeviceDescriptionOp(Napi::Env env, FT_HANDLE ftHandle, std::string description);
    void Execute() override;
    void OnOK() override;

private:
    FT_HANDLE ftHandle;
    char description[64];
    inline static FT_STATUS FtExProgramDeviceDescription(FT_HANDLE ftHandle, const char* description);
};

#endif // FT_EX_PROGRAM_DEVICE_DESCRIPTION_OP_H_
