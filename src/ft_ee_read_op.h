#ifndef FT_EE_READ_OP_H_
#define FT_EE_READ_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"
#include "ft_program_data_wrapper.h"

class FtEeReadOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtEeReadOp(Napi::Env env, FT_HANDLE ftHandle, FtProgramDataWrapper *pftProgramDataWrapper);
    void Execute() override;
    void OnOK() override;
    void Destroy() override;

private:
    FT_HANDLE ftHandle;
    FtProgramDataWrapper *pftProgramDataWrapper;
};

#endif // FT_EE_READ_OP_H_