#ifndef FT_SET_FLOW_CONTROL_OP_H_
#define FT_SET_FLOW_CONTROL_OP_H_

#include <napi.h>
#include <ftd2xx.h>
#include "ft_base_op.h"
#include "ft_handler_wrapper.h"

class FtSetFlowControlOp : public FtBaseOp
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
    static Napi::Promise Invoke(const Napi::CallbackInfo &info);
    FtSetFlowControlOp(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff);
    void Execute();
    void OnOK();

private:
    FT_HANDLE ftHandle;
    USHORT flowControl;
    UCHAR xon;
    UCHAR xoff;
};

#endif // FT_SET_FLOW_CONTROL_OP_H_