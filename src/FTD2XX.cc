#include <napi.h>
#include <ftd2xx.h>
#if !_WIN32
#include <WinTypes.h>
#endif

Napi::Object CreateFtResultObject(Napi::Env env, FT_STATUS ftStatus)
{
  Napi::Object nObj = Napi::Object::New(env);
  nObj.Set("ftStatus", ftStatus);
  return nObj;
}

Napi::Object CreateFtHandleWrapper(Napi::Env env, FT_HANDLE ftHandle)
{
  Napi::Object nObj = Napi::Object::New(env);
  nObj.Set("value", (uintptr_t)ftHandle);
  nObj.Set("_external", Napi::External<void>::New(env, ftHandle));
  return nObj;
}

FT_HANDLE GetFtHandleFromWrapper(Napi::Value wrapper)
{
  Napi::External<void> ext = wrapper.As<Napi::Object>().Get("_external").As<Napi::External<void>>();
  return ext.Data();
}

Napi::Object CreateDeviceInfoList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  DWORD devCount;
  FT_STATUS ftStatus = FT_CreateDeviceInfoList(&devCount);
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("devCount", devCount);
  return result;
}

Napi::Object GetDeviceInfoDetail(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  DWORD flags;
  DWORD id;
  DWORD type;
  DWORD locId;
  char serialNumber[16];
  char description[64];
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  Napi::Object deviceInfo = Napi::Object::New(env);
  deviceInfo.Set("flags", flags);
  deviceInfo.Set("type", type);
  deviceInfo.Set("id", id);
  deviceInfo.Set("locId", locId);
  deviceInfo.Set("serialNumber", serialNumber);
  deviceInfo.Set("description", description);
  deviceInfo.Set("ftHandle", CreateFtHandleWrapper(env, ftHandle));
  result.Set("deviceInfo", deviceInfo);
  return result;
}

Napi::Object Open(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_Open(index, &ftHandle);
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", CreateFtHandleWrapper(env, ftHandle));
  return result;
}

Napi::Object OpenEx(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Value arg1 = info[0];
  PVOID pvArg1;
  printf("!!!!!!!!!!!11Hello\n");
  printf(arg1.IsString() ? "true\n" : "false\n");
  std::string snOrDsc;
  long locId = 0;
  if (arg1.IsString())
  {
    snOrDsc = arg1.As<Napi::String>().Utf8Value();
    pvArg1 = &snOrDsc;
  }
  else
  {
    pvArg1 = (void*)arg1.As<Napi::Number>().Int64Value();
  }
  DWORD flags = info[1].As<Napi::Number>().Int64Value();
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", CreateFtHandleWrapper(env, ftHandle));
  return result;
}

Napi::Number Close(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  FT_HANDLE ftHandle = GetFtHandleFromWrapper(info[0]);
  FT_STATUS ftStatus = FT_Close(ftHandle);
  return Napi::Number::New(env, ftStatus);
}

Napi::Number SetDataCharacteristics(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  FT_HANDLE ftHandle = GetFtHandleFromWrapper(info[0]);
  UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
  UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
  UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
  return Napi::Number::New(env, ftStatus);
}

Napi::Number SetFlowControl(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  FT_HANDLE ftHandle = GetFtHandleFromWrapper(info[0]);
  USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
  UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
  UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
  return Napi::Number::New(env, ftStatus);
}

Napi::Number SetBaudRate(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  FT_HANDLE ftHandle = GetFtHandleFromWrapper(info[0]);
  ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetBaudRate(ftHandle, baudRate);
  return Napi::Number::New(env, ftStatus);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "createDeviceInfoList"), Napi::Function::New(env, CreateDeviceInfoList));
  exports.Set(Napi::String::New(env, "getDeviceInfoDetail"), Napi::Function::New(env, GetDeviceInfoDetail));
  exports.Set(Napi::String::New(env, "open"), Napi::Function::New(env, Open));
  exports.Set(Napi::String::New(env, "openEx"), Napi::Function::New(env, OpenEx));
  exports.Set(Napi::String::New(env, "close"), Napi::Function::New(env, Close));
  exports.Set(Napi::String::New(env, "setDataCharacteristics"), Napi::Function::New(env, SetDataCharacteristics));
  exports.Set(Napi::String::New(env, "setFlowControl"), Napi::Function::New(env, SetFlowControl));
  exports.Set(Napi::String::New(env, "setBaudRate"), Napi::Function::New(env, SetBaudRate));
  return exports;
}

NODE_API_MODULE(addon, Init)
