#ifndef FT_HANDLER_WRAPPER_H_
#define FT_HANDLER_WRAPPER_H_
#include <napi.h>
#if !_WIN32
#include <WinTypes.h>
#endif

class FtHandlerWrapper : public Napi::ObjectWrap<FtHandlerWrapper>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, PVOID ftHandle);
  static PVOID GetFtHandler(Napi::Value value);
  FtHandlerWrapper(const Napi::CallbackInfo &info);
  ~FtHandlerWrapper();
  PVOID GetFtHandler();

private:
  PVOID _ftHandle;
  static Napi::FunctionReference constructor;
  void Free(const Napi::CallbackInfo &info);
};
#endif
