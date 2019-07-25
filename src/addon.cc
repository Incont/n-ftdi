#include <napi.h>
#include <ftd2xx.h>
#if !_WIN32
#include <WinTypes.h>
#endif

Napi::Object CreateDeviceInfoList(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  FT_STATUS ftStatus;
  DWORD devCount;
  // create the device information list
  ftStatus = FT_CreateDeviceInfoList(&devCount);

  Napi::Number n_ftStatus = Napi::Number::New(env, ftStatus);
  Napi::Number n_devCount = Napi::Number::New(env, devCount);
  Napi::Object result = Napi::Object::New(env);
  result.Set(Napi::String::New(env, "ftStatus"), n_ftStatus);
  result.Set(Napi::String::New(env, "devCount"), n_devCount);
  return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "createDeviceInfoList"),
              Napi::Function::New(env, CreateDeviceInfoList));
  return exports;
}

NODE_API_MODULE(addon, Init)
