#include <napi.h>
#include <ftd2xx.h>
#if !_WIN32
#include <WinTypes.h>
#endif

inline Napi::Object CreateFtResultObject(Napi::Env env, FT_STATUS ftStatus)
{
  Napi::Object nObj = Napi::Object::New(env);
  nObj.Set("ftStatus", ftStatus);
  return nObj;
}

////////////////////////////////////////////////////////////////////////////////
// FtHandlerWrapper class
////////////////////////////////////////////////////////////////////////////////

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
  FT_HANDLE ftHandle;
  static Napi::FunctionReference constructor;
  void Free(const Napi::CallbackInfo &info);
};

Napi::FunctionReference FtHandlerWrapper::constructor;

Napi::Object FtHandlerWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(
      env,
      "FtHandler",
      {InstanceMethod("free", &FtHandlerWrapper::Free)});
  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("FtHandler", func);
  return exports;
}

Napi::Object FtHandlerWrapper::NewInstance(Napi::Env env, FT_HANDLE ftHandle)
{
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({});
  FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(obj);
  wrapper->ftHandle = ftHandle;
  return scope.Escape(napi_value(obj)).ToObject();
}

FT_HANDLE FtHandlerWrapper::GetFtHandler(Napi::Value value)
{
  FtHandlerWrapper *wrapper = Napi::ObjectWrap<FtHandlerWrapper>::Unwrap(value.As<Napi::Object>());
  return wrapper->GetFtHandler();
}

FtHandlerWrapper::FtHandlerWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<FtHandlerWrapper>(info) {}

void FtHandlerWrapper::Free(const Napi::CallbackInfo &info)
{
  this->ftHandle = nullptr;
}

FtHandlerWrapper::~FtHandlerWrapper()
{
  if (this->ftHandle != nullptr)
    FT_Close(this->ftHandle);
}

FT_HANDLE FtHandlerWrapper::GetFtHandler()
{
  return ftHandle;
}

////////////////////////////////////////////////////////////////////////////////
// CreateDeviceInfoListWorker class
////////////////////////////////////////////////////////////////////////////////

class CreateDeviceInfoListWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  DWORD devCount;
  CreateDeviceInfoListWorker(Napi::Env env);
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount);
};

Napi::Object CreateDeviceInfoListWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("createDeviceInfoListSync", Napi::Function::New(env, CreateDeviceInfoListWorker::InvokeSync));
  exports.Set("createDeviceInfoList", Napi::Function::New(env, CreateDeviceInfoListWorker::Invoke));
  return exports;
}

Napi::Object CreateDeviceInfoListWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  DWORD devCount;
  FT_STATUS ftStatus = FT_CreateDeviceInfoList(&devCount);
  return CreateResult(info.Env(), ftStatus, devCount);
}

Napi::Promise CreateDeviceInfoListWorker::Invoke(const Napi::CallbackInfo &info)
{
  auto *worker = new CreateDeviceInfoListWorker(info.Env());
  worker->Queue();
  return worker->deferred.Promise();
}

CreateDeviceInfoListWorker::CreateDeviceInfoListWorker(Napi::Env env)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)) {}

void CreateDeviceInfoListWorker::Execute()
{
  ftStatus = FT_CreateDeviceInfoList(&devCount);
}

void CreateDeviceInfoListWorker::OnOK()
{
  Napi::HandleScope scope(AsyncWorker::Env());
  deferred.Resolve(CreateResult(AsyncWorker::Env(), ftStatus, devCount));
}

Napi::Object CreateDeviceInfoListWorker::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("devCount", devCount);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// GetDeviceInfoDetailWorker class
////////////////////////////////////////////////////////////////////////////////

class GetDeviceInfoDetailWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  DWORD index;
  DWORD flags;
  DWORD id;
  DWORD type;
  DWORD locId;
  char serialNumber[16];
  char description[64];
  FT_HANDLE ftHandle;
  GetDeviceInfoDetailWorker(Napi::Env env, DWORD index);
  inline static Napi::Object CreateResult(
      Napi::Env env,
      FT_STATUS ftStatus,
      DWORD flags,
      DWORD id,
      DWORD type,
      DWORD locId,
      char *serialNumber,
      char *description,
      FT_HANDLE ftHandle);
};

Napi::Object GetDeviceInfoDetailWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("getDeviceInfoDetailSync", Napi::Function::New(env, GetDeviceInfoDetailWorker::InvokeSync));
  exports.Set("getDeviceInfoDetail", Napi::Function::New(env, GetDeviceInfoDetailWorker::Invoke));
  return exports;
}

Napi::Object GetDeviceInfoDetailWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  DWORD flags;
  DWORD id;
  DWORD type;
  DWORD locId;
  char serialNumber[16];
  char description[64];
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
  return CreateResult(info.Env(), ftStatus, flags, id, type, locId, serialNumber, description, ftHandle);
}

Napi::Promise GetDeviceInfoDetailWorker::Invoke(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  auto *worker = new GetDeviceInfoDetailWorker(info.Env(), index);
  worker->Queue();
  return worker->deferred.Promise();
}

GetDeviceInfoDetailWorker::GetDeviceInfoDetailWorker(Napi::Env env, DWORD index)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), index(index) {}

void GetDeviceInfoDetailWorker::Execute()
{
  ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
}

void GetDeviceInfoDetailWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, flags, id, type, locId, serialNumber, description, ftHandle));
}

Napi::Object GetDeviceInfoDetailWorker::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    DWORD flags,
    DWORD id, DWORD type,
    DWORD locId,
    char *serialNumber,
    char *description,
    FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  Napi::Object deviceInfo = Napi::Object::New(env);
  Napi::Value nFtHandler = ftHandle == nullptr
                               ? env.Null()
                               : FtHandlerWrapper::NewInstance(env, ftHandle);
  deviceInfo.Set("flags", flags);
  deviceInfo.Set("type", type);
  deviceInfo.Set("id", id);
  deviceInfo.Set("locId", locId);
  deviceInfo.Set("serialNumber", serialNumber);
  deviceInfo.Set("description", description);
  deviceInfo.Set("ftHandle", nFtHandler);
  result.Set("deviceInfo", deviceInfo);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// OpenWorker class
////////////////////////////////////////////////////////////////////////////////

class OpenWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  DWORD index;
  FT_HANDLE ftHandle;
  OpenWorker(Napi::Env env, DWORD index);
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

Napi::Object OpenWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("openSync", Napi::Function::New(env, OpenWorker::InvokeSync));
  exports.Set("open", Napi::Function::New(env, OpenWorker::Invoke));
  return exports;
}

Napi::Object OpenWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_Open(index, &ftHandle);
  return CreateResult(info.Env(), ftStatus, ftHandle);
}

Napi::Promise OpenWorker::Invoke(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  auto *worker = new OpenWorker(info.Env(), index);
  worker->Queue();
  return worker->deferred.Promise();
}

OpenWorker::OpenWorker(Napi::Env env, DWORD index)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), index(index) {}

void OpenWorker::Execute()
{
  ftStatus = FT_Open(index, &ftHandle);
}

void OpenWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object OpenWorker::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", FtHandlerWrapper::NewInstance(env, ftHandle));
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// OpenExWorker class
////////////////////////////////////////////////////////////////////////////////

class OpenExWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  PVOID pvArg1;
  DWORD flags;
  FT_HANDLE ftHandle;
  OpenExWorker(Napi::Env env, PVOID pvArg1, DWORD flags);
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

Napi::Object OpenExWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("openExSync", Napi::Function::New(env, OpenExWorker::InvokeSync));
  exports.Set("openEx", Napi::Function::New(env, OpenExWorker::Invoke));
  return exports;
}

Napi::Object OpenExWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  PVOID pvArg1;
  std::string snOrDsc;
  if (info[0].IsString())
  {
    snOrDsc = info[0].As<Napi::String>().Utf8Value();
    pvArg1 = (void *)snOrDsc.c_str();
  }
  else
  {
    pvArg1 = (void *)info[0].As<Napi::Number>().Int64Value();
  }
  DWORD flags = info[1].As<Napi::Number>().Int64Value();
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
  return CreateResult(info.Env(), ftStatus, ftHandle);
}

Napi::Promise OpenExWorker::Invoke(const Napi::CallbackInfo &info)
{
  PVOID pvArg1;
  std::string snOrDsc;
  if (info[0].IsString())
  {
    snOrDsc = info[0].As<Napi::String>().Utf8Value();
    pvArg1 = (void *)snOrDsc.c_str();
  }
  else
  {
    pvArg1 = (void *)info[0].As<Napi::Number>().Int64Value();
  }
  DWORD flags = info[1].As<Napi::Number>().Int64Value();
  auto *worker = new OpenExWorker(info.Env(), pvArg1, flags);
  worker->Queue();
  return worker->deferred.Promise();
}

OpenExWorker::OpenExWorker(Napi::Env env, PVOID pvArg1, DWORD flags)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), pvArg1(pvArg1), flags(flags) {}

void OpenExWorker::Execute()
{
  ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
}

void OpenExWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object OpenExWorker::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", FtHandlerWrapper::NewInstance(env, ftHandle));
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// CloseWorker class
////////////////////////////////////////////////////////////////////////////////

class CloseWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;
  CloseWorker(Napi::Env env, FT_HANDLE ftHandle);
};

Napi::Object CloseWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("closeSync", Napi::Function::New(env, CloseWorker::InvokeSync));
  exports.Set("close", Napi::Function::New(env, CloseWorker::Invoke));
  return exports;
}

Napi::Number CloseWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  FT_STATUS ftStatus = FT_Close(ftHandle);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise CloseWorker::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  auto *worker = new CloseWorker(info.Env(), ftHandle);
  worker->Queue();
  return worker->deferred.Promise();
}

CloseWorker::CloseWorker(Napi::Env env, FT_HANDLE ftHandle)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), ftHandle(ftHandle) {}

void CloseWorker::Execute()
{
  ftStatus = FT_Close(ftHandle);
}

void CloseWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetDataCharacteristicsWorker class
////////////////////////////////////////////////////////////////////////////////

class SetDataCharacteristicsWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;
  UCHAR wordLength;
  UCHAR stopBits;
  UCHAR parity;
  SetDataCharacteristicsWorker(Napi::Env env, FT_HANDLE ftHandle, UCHAR wordLength, UCHAR stopBits, UCHAR parity);
};

Napi::Object SetDataCharacteristicsWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setDataCharacteristicsSync", Napi::Function::New(env, SetDataCharacteristicsWorker::InvokeSync));
  exports.Set("SetDataCharacteristics", Napi::Function::New(env, SetDataCharacteristicsWorker::Invoke));
  return exports;
}

Napi::Number SetDataCharacteristicsWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
  UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
  UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetDataCharacteristicsWorker::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
  UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
  UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
  auto *worker = new SetDataCharacteristicsWorker(info.Env(), ftHandle, wordLength, stopBits, parity);
  worker->Queue();
  return worker->deferred.Promise();
}

SetDataCharacteristicsWorker::SetDataCharacteristicsWorker(Napi::Env env, FT_HANDLE ftHandle, UCHAR wordLength, UCHAR stopBits, UCHAR parity)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), ftHandle(ftHandle), wordLength(wordLength), stopBits(stopBits), parity(parity) {}

void SetDataCharacteristicsWorker::Execute()
{
  ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
}

void SetDataCharacteristicsWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetFlowControlWorker class
////////////////////////////////////////////////////////////////////////////////

class SetFlowControlWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;
  USHORT flowControl;
  UCHAR xon;
  UCHAR xoff;
  SetFlowControlWorker(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff);
};

Napi::Object SetFlowControlWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setFlowControlSync", Napi::Function::New(env, SetFlowControlWorker::InvokeSync));
  exports.Set("setFlowControl", Napi::Function::New(env, SetFlowControlWorker::Invoke));
  return exports;
}

Napi::Number SetFlowControlWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
  UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
  UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetFlowControlWorker::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
  UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
  UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
  auto *worker = new SetFlowControlWorker(info.Env(), ftHandle, flowControl, xon, xoff);
  worker->Queue();
  return worker->deferred.Promise();
}

SetFlowControlWorker::SetFlowControlWorker(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), ftHandle(ftHandle), flowControl(flowControl), xon(xon), xoff(xoff) {}

void SetFlowControlWorker::Execute()
{
  ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
}

void SetFlowControlWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetBaudRateWorker class
////////////////////////////////////////////////////////////////////////////////

class SetBaudRateWorker : public Napi::AsyncWorker
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  void Execute();
  void OnOK();

private:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;
  ULONG baudRate;
  SetBaudRateWorker(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate);
};

Napi::Object SetBaudRateWorker::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setBaudRateSync", Napi::Function::New(env, SetBaudRateWorker::InvokeSync));
  exports.Set("setBaudRate", Napi::Function::New(env, SetBaudRateWorker::Invoke));
  return exports;
}

Napi::Number SetBaudRateWorker::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetBaudRate(ftHandle, baudRate);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetBaudRateWorker::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
  auto *worker = new SetBaudRateWorker(info.Env(), ftHandle, baudRate);
  worker->Queue();
  return worker->deferred.Promise();
}

SetBaudRateWorker::SetBaudRateWorker(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate)
    : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), ftHandle(ftHandle), baudRate(baudRate) {}

void SetBaudRateWorker::Execute()
{
  ftStatus = FT_SetBaudRate(ftHandle, baudRate);
}

void SetBaudRateWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  FtHandlerWrapper::Init(env, exports);
  CreateDeviceInfoListWorker::Init(env, exports);
  GetDeviceInfoDetailWorker::Init(env, exports);
  OpenWorker::Init(env, exports);
  OpenExWorker::Init(env, exports);
  CloseWorker::Init(env, exports);
  SetDataCharacteristicsWorker::Init(env, exports);
  SetFlowControlWorker::Init(env, exports);
  SetBaudRateWorker::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)