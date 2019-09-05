#ifndef FT_HANDLER_WRAPPER_H_
#define FT_HANDLER_WRAPPER_H_

#include <napi.h>
#include <ftd2xx.h>

class FtHandlerWrapper : public Napi::ObjectWrap<FtHandlerWrapper>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Env env, FT_HANDLE ftHandle);
    static FT_HANDLE GetFtHandler(Napi::Value value);
    FtHandlerWrapper(const Napi::CallbackInfo &info);
    ~FtHandlerWrapper();
    FT_HANDLE GetFtHandler();

private:
    static Napi::FunctionReference constructor;
    FT_HANDLE ftHandle;
    void Free(const Napi::CallbackInfo &info);
};

#endif // FT_HANDLER_WRAPPER_H_