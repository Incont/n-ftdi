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
// BaseFtdiOp class
////////////////////////////////////////////////////////////////////////////////
class BaseFtdiOp : public Napi::AsyncWorker
{
public:
  BaseFtdiOp(Napi::Env env);
  Napi::Promise Promise();

protected:
  Napi::Promise::Deferred deferred;
  FT_STATUS ftStatus;
};

BaseFtdiOp::BaseFtdiOp(Napi::Env env) : Napi::AsyncWorker(env, "ftdi"), deferred(Napi::Promise::Deferred::New(env)) {}
Napi::Promise BaseFtdiOp::Promise()
{
  return deferred.Promise();
}

////////////////////////////////////////////////////////////////////////////////
// CreateDeviceInfoListOp class
////////////////////////////////////////////////////////////////////////////////

class CreateDeviceInfoListOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  CreateDeviceInfoListOp(Napi::Env env);
  void Execute();
  void OnOK();

private:
  DWORD devCount;
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount);
};

Napi::Object CreateDeviceInfoListOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("createDeviceInfoListSync", Napi::Function::New(env, CreateDeviceInfoListOp::InvokeSync));
  exports.Set("createDeviceInfoList", Napi::Function::New(env, CreateDeviceInfoListOp::Invoke));
  return exports;
}

Napi::Object CreateDeviceInfoListOp::InvokeSync(const Napi::CallbackInfo &info)
{
  DWORD devCount;
  FT_STATUS ftStatus = FT_CreateDeviceInfoList(&devCount);
  return CreateResult(info.Env(), ftStatus, devCount);
}

Napi::Promise CreateDeviceInfoListOp::Invoke(const Napi::CallbackInfo &info)
{
  auto *operation = new CreateDeviceInfoListOp(info.Env());
  operation->Queue();
  return operation->Promise();
}

CreateDeviceInfoListOp::CreateDeviceInfoListOp(Napi::Env env) : BaseFtdiOp(env) {}

void CreateDeviceInfoListOp::Execute()
{
  ftStatus = FT_CreateDeviceInfoList(&devCount);
}

void CreateDeviceInfoListOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, devCount));
}

Napi::Object CreateDeviceInfoListOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, DWORD devCount)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("devCount", devCount);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// GetDeviceInfoDetailOp class
////////////////////////////////////////////////////////////////////////////////

class GetDeviceInfoDetailOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  GetDeviceInfoDetailOp(Napi::Env env, DWORD index);
  void Execute();
  void OnOK();

private:
  DWORD index;
  DWORD flags;
  DWORD id;
  DWORD type;
  DWORD locId;
  char serialNumber[16];
  char description[64];
  FT_HANDLE ftHandle;
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

Napi::Object GetDeviceInfoDetailOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("getDeviceInfoDetailSync", Napi::Function::New(env, GetDeviceInfoDetailOp::InvokeSync));
  exports.Set("getDeviceInfoDetail", Napi::Function::New(env, GetDeviceInfoDetailOp::Invoke));
  return exports;
}

Napi::Object GetDeviceInfoDetailOp::InvokeSync(const Napi::CallbackInfo &info)
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

Napi::Promise GetDeviceInfoDetailOp::Invoke(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  auto *operation = new GetDeviceInfoDetailOp(info.Env(), index);
  operation->Queue();
  return operation->Promise();
}

GetDeviceInfoDetailOp::GetDeviceInfoDetailOp(Napi::Env env, DWORD index) : BaseFtdiOp(env), index(index) {}

void GetDeviceInfoDetailOp::Execute()
{
  ftStatus = FT_GetDeviceInfoDetail(index, &flags, &type, &id, &locId, serialNumber, description, &ftHandle);
}

void GetDeviceInfoDetailOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, flags, id, type, locId, serialNumber, description, ftHandle));
}

Napi::Object GetDeviceInfoDetailOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    DWORD flags,
    DWORD id,
    DWORD type,
    DWORD locId,
    char *serialNumber,
    char *description,
    FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  Napi::Object deviceInfoDetail = Napi::Object::New(env);
  Napi::Value nFtHandler = ftHandle == nullptr
                               ? env.Null()
                               : FtHandlerWrapper::NewInstance(env, ftHandle);
  deviceInfoDetail.Set("flags", flags);
  deviceInfoDetail.Set("type", type);
  deviceInfoDetail.Set("id", id);
  deviceInfoDetail.Set("locId", locId);
  deviceInfoDetail.Set("serialNumber", serialNumber);
  deviceInfoDetail.Set("description", description);
  deviceInfoDetail.Set("ftHandle", nFtHandler);
  result.Set("deviceInfoDetail", deviceInfoDetail);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// OpenOp class
////////////////////////////////////////////////////////////////////////////////

class OpenOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  OpenOp(Napi::Env env, DWORD index);
  void Execute();
  void OnOK();

private:
  DWORD index;
  FT_HANDLE ftHandle;
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

Napi::Object OpenOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("openSync", Napi::Function::New(env, OpenOp::InvokeSync));
  exports.Set("open", Napi::Function::New(env, OpenOp::Invoke));
  return exports;
}

Napi::Object OpenOp::InvokeSync(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus = FT_Open(index, &ftHandle);
  return CreateResult(info.Env(), ftStatus, ftHandle);
}

Napi::Promise OpenOp::Invoke(const Napi::CallbackInfo &info)
{
  DWORD index = info[0].As<Napi::Number>().Int32Value();
  auto *operation = new OpenOp(info.Env(), index);
  operation->Queue();
  return operation->Promise();
}

OpenOp::OpenOp(Napi::Env env, DWORD index) : BaseFtdiOp(env), index(index) {}

void OpenOp::Execute()
{
  ftStatus = FT_Open(index, &ftHandle);
}

void OpenOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object OpenOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", FtHandlerWrapper::NewInstance(env, ftHandle));
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// OpenExOp class
////////////////////////////////////////////////////////////////////////////////

class OpenExOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  OpenExOp(Napi::Env env, PVOID pvArg1, DWORD flags);
  void Execute();
  void OnOK();

private:
  PVOID pvArg1;
  DWORD flags;
  FT_HANDLE ftHandle;
  inline static Napi::Object CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle);
};

Napi::Object OpenExOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("openExSync", Napi::Function::New(env, OpenExOp::InvokeSync));
  exports.Set("openEx", Napi::Function::New(env, OpenExOp::Invoke));
  return exports;
}

Napi::Object OpenExOp::InvokeSync(const Napi::CallbackInfo &info)
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

Napi::Promise OpenExOp::Invoke(const Napi::CallbackInfo &info)
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
  auto *operation = new OpenExOp(info.Env(), pvArg1, flags);
  operation->Queue();
  return operation->Promise();
}

OpenExOp::OpenExOp(Napi::Env env, PVOID pvArg1, DWORD flags) : BaseFtdiOp(env), pvArg1(pvArg1), flags(flags) {}

void OpenExOp::Execute()
{
  ftStatus = FT_OpenEx(pvArg1, flags, &ftHandle);
}

void OpenExOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftHandle));
}

Napi::Object OpenExOp::CreateResult(Napi::Env env, FT_STATUS ftStatus, FT_HANDLE ftHandle)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftHandle", FtHandlerWrapper::NewInstance(env, ftHandle));
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// CloseOp class
////////////////////////////////////////////////////////////////////////////////

class CloseOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  CloseOp(Napi::Env env, FT_HANDLE ftHandle);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
};

Napi::Object CloseOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("closeSync", Napi::Function::New(env, CloseOp::InvokeSync));
  exports.Set("close", Napi::Function::New(env, CloseOp::Invoke));
  return exports;
}

Napi::Number CloseOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  FT_STATUS ftStatus = FT_Close(ftHandle);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise CloseOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  auto *operation = new CloseOp(info.Env(), ftHandle);
  operation->Queue();
  return operation->Promise();
}

CloseOp::CloseOp(Napi::Env env, FT_HANDLE ftHandle) : BaseFtdiOp(env), ftHandle(ftHandle) {}

void CloseOp::Execute()
{
  ftStatus = FT_Close(ftHandle);
}

void CloseOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetDataCharacteristicsOp class
////////////////////////////////////////////////////////////////////////////////

class SetDataCharacteristicsOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  SetDataCharacteristicsOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR wordLength, UCHAR stopBits, UCHAR parity);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
  UCHAR wordLength;
  UCHAR stopBits;
  UCHAR parity;
};

Napi::Object SetDataCharacteristicsOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setDataCharacteristicsSync", Napi::Function::New(env, SetDataCharacteristicsOp::InvokeSync));
  exports.Set("SetDataCharacteristics", Napi::Function::New(env, SetDataCharacteristicsOp::Invoke));
  return exports;
}

Napi::Number SetDataCharacteristicsOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
  UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
  UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetDataCharacteristicsOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  UCHAR wordLength = info[1].As<Napi::Number>().Uint32Value();
  UCHAR stopBits = info[2].As<Napi::Number>().Uint32Value();
  UCHAR parity = info[3].As<Napi::Number>().Uint32Value();
  auto *operation = new SetDataCharacteristicsOp(info.Env(), ftHandle, wordLength, stopBits, parity);
  operation->Queue();
  return operation->Promise();
}

SetDataCharacteristicsOp::SetDataCharacteristicsOp(Napi::Env env, FT_HANDLE ftHandle, UCHAR wordLength, UCHAR stopBits, UCHAR parity)
    : BaseFtdiOp(env), ftHandle(ftHandle), wordLength(wordLength), stopBits(stopBits), parity(parity) {}

void SetDataCharacteristicsOp::Execute()
{
  ftStatus = FT_SetDataCharacteristics(ftHandle, wordLength, stopBits, parity);
}

void SetDataCharacteristicsOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetFlowControlOp class
////////////////////////////////////////////////////////////////////////////////

class SetFlowControlOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  SetFlowControlOp(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
  USHORT flowControl;
  UCHAR xon;
  UCHAR xoff;
};

Napi::Object SetFlowControlOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setFlowControlSync", Napi::Function::New(env, SetFlowControlOp::InvokeSync));
  exports.Set("setFlowControl", Napi::Function::New(env, SetFlowControlOp::Invoke));
  return exports;
}

Napi::Number SetFlowControlOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
  UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
  UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetFlowControlOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  USHORT flowControl = info[1].As<Napi::Number>().Uint32Value();
  UCHAR xon = info[2].As<Napi::Number>().Uint32Value();
  UCHAR xoff = info[3].As<Napi::Number>().Uint32Value();
  auto *operation = new SetFlowControlOp(info.Env(), ftHandle, flowControl, xon, xoff);
  operation->Queue();
  return operation->Promise();
}

SetFlowControlOp::SetFlowControlOp(Napi::Env env, FT_HANDLE ftHandle, USHORT flowControl, UCHAR xon, UCHAR xoff)
    : BaseFtdiOp(env), ftHandle(ftHandle), flowControl(flowControl), xon(xon), xoff(xoff) {}

void SetFlowControlOp::Execute()
{
  ftStatus = FT_SetFlowControl(ftHandle, flowControl, xon, xoff);
}

void SetFlowControlOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// SetBaudRateOp class
////////////////////////////////////////////////////////////////////////////////

class SetBaudRateOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Number InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  SetBaudRateOp(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
  ULONG baudRate;
};

Napi::Object SetBaudRateOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("setBaudRateSync", Napi::Function::New(env, SetBaudRateOp::InvokeSync));
  exports.Set("setBaudRate", Napi::Function::New(env, SetBaudRateOp::Invoke));
  return exports;
}

Napi::Number SetBaudRateOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
  FT_STATUS ftStatus = FT_SetBaudRate(ftHandle, baudRate);
  return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise SetBaudRateOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  ULONG baudRate = info[1].As<Napi::Number>().Uint32Value();
  auto *operation = new SetBaudRateOp(info.Env(), ftHandle, baudRate);
  operation->Queue();
  return operation->Promise();
}

SetBaudRateOp::SetBaudRateOp(Napi::Env env, FT_HANDLE ftHandle, ULONG baudRate)
    : BaseFtdiOp(env), ftHandle(ftHandle), baudRate(baudRate) {}

void SetBaudRateOp::Execute()
{
  ftStatus = FT_SetBaudRate(ftHandle, baudRate);
}

void SetBaudRateOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
// GetDeviceInfoOp class
////////////////////////////////////////////////////////////////////////////////

class GetDeviceInfoOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  GetDeviceInfoOp(Napi::Env env, FT_HANDLE ftHandle);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
  FT_DEVICE ftDevice;
  DWORD deviceID;
  char serialNumber[16];
  char description[64];
  inline static Napi::Object CreateResult(
      Napi::Env env,
      FT_STATUS ftStatus,
      FT_DEVICE ftDevice,
      DWORD deviceID,
      char *serialNumber,
      char *description);
};

Napi::Object GetDeviceInfoOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("getDeviceInfoSync", Napi::Function::New(env, GetDeviceInfoOp::InvokeSync));
  exports.Set("getDeviceInfo", Napi::Function::New(env, GetDeviceInfoOp::Invoke));
  return exports;
}

Napi::Object GetDeviceInfoOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  FT_DEVICE ftDevice;
  DWORD deviceID;
  char serialNumber[16];
  char description[64];
  FT_STATUS ftStatus =  FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceID, serialNumber, description, nullptr);
  return CreateResult(info.Env(), ftStatus, ftDevice, deviceID, serialNumber, description);
}

Napi::Promise GetDeviceInfoOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  auto *operation = new GetDeviceInfoOp(info.Env(), ftHandle);
  operation->Queue();
  return operation->Promise();
}

GetDeviceInfoOp::GetDeviceInfoOp(Napi::Env env, FT_HANDLE ftHandle) : BaseFtdiOp(env), ftHandle(ftHandle) {}

void GetDeviceInfoOp::Execute()
{
  ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceID, serialNumber, description, nullptr);
}

void GetDeviceInfoOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftDevice, deviceID, serialNumber, description));
}

Napi::Object GetDeviceInfoOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    FT_DEVICE ftDevice,
    DWORD deviceID,
    char *serialNumber,
    char *description)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftDevice", ftDevice);
  result.Set("deviceID", deviceID);
  result.Set("serialNumber", serialNumber);
  result.Set("description", description);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  FtHandlerWrapper::Init(env, exports);
  CreateDeviceInfoListOp::Init(env, exports);
  GetDeviceInfoDetailOp::Init(env, exports);
  OpenOp::Init(env, exports);
  OpenExOp::Init(env, exports);
  CloseOp::Init(env, exports);
  SetDataCharacteristicsOp::Init(env, exports);
  SetFlowControlOp::Init(env, exports);
  SetBaudRateOp::Init(env, exports);
  GetDeviceInfoOp::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)
