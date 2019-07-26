#include <napi.h>
#include <ftd2xx.h>
#if !_WIN32
#include <WinTypes.h>
#endif

Napi::Object CreateFtHandleWrapper(Napi::Env env, FT_HANDLE ftHandle)
{
  Napi::Object nObj = Napi::Object::New(env);
  nObj.Set("value", (uintptr_t)ftHandle);
  nObj.Set("external", Napi::External<FT_HANDLE>::New(env, &ftHandle));
  return nObj;
}

Napi::Object CreateDeviceInfoList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  DWORD devCount;
  FT_STATUS ftStatus = FT_CreateDeviceInfoList(&devCount);

  Napi::Object result = Napi::Object::New(env);
  result.Set("ftStatus", ftStatus);
  result.Set("devCount", devCount);
  return result;
}

Napi::Object GetDeviceInfoDetail(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  DWORD flags;
  DWORD id;
  DWORD type;
  DWORD locId;
  char serialNumber[16];
  char description[64];
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_GetDeviceInfoDetail(info[0].As<Napi::Number>().Int32Value(),
                                              &flags, &type, &id, &locId, serialNumber, description, &ftHandle);

  Napi::Object result = Napi::Object::New(env);
  Napi::Object deviceInfo = Napi::Object::New(env);
  deviceInfo.Set("flags", flags);
  deviceInfo.Set("type", type);
  deviceInfo.Set("id", id);
  deviceInfo.Set("locId", locId);
  deviceInfo.Set("serialNumber", serialNumber);
  deviceInfo.Set("description", description);
  deviceInfo.Set("ftHandle", CreateFtHandleWrapper(env, ftHandle));
  result.Set("ftStatus", flags);
  result.Set("deviceInfo", deviceInfo);
  return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "createDeviceInfoList"), Napi::Function::New(env, CreateDeviceInfoList));
  exports.Set(Napi::String::New(env, "getDeviceInfoDetail"), Napi::Function::New(env, GetDeviceInfoDetail));
  return exports;
}

NODE_API_MODULE(addon, Init)
