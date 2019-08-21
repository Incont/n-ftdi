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
  static Napi::FunctionReference constructor;
  FT_HANDLE ftHandle;
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
// FtProgramDataWrapper class
////////////////////////////////////////////////////////////////////////////////

class FtProgramDataWrapper : public Napi::ObjectWrap<FtProgramDataWrapper>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, FT_HANDLE ftHandle);
  static PFT_PROGRAM_DATA GetData(Napi::Value value);
  FtProgramDataWrapper(const Napi::CallbackInfo &info);
  PFT_PROGRAM_DATA GetData();

private:
  static Napi::FunctionReference constructor;
  char manufacturer[32];
  char manufacturerId[16];
  char description[64];
  char serialNumber[16];
  FT_PROGRAM_DATA ftData;
  Napi::Value GetSignature1(const Napi::CallbackInfo &info);
  void SetSignature1(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetSignature2(const Napi::CallbackInfo &info);
  void SetSignature2(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetVersion(const Napi::CallbackInfo &info);
  void SetVersion(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetVendorId(const Napi::CallbackInfo &info);
  void SetVendorId(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetProductId(const Napi::CallbackInfo &info);
  void SetProductId(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetManufacturer(const Napi::CallbackInfo &info);
  void SetManufacturer(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetManufacturerId(const Napi::CallbackInfo &info);
  void SetManufacturerId(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetDescription(const Napi::CallbackInfo &info);
  void SetDescription(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetSerialNumber(const Napi::CallbackInfo &info);
  void SetSerialNumber(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetMaxPower(const Napi::CallbackInfo &info);
  void SetMaxPower(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetPnP(const Napi::CallbackInfo &info);
  void SetPnP(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetSelfPowered(const Napi::CallbackInfo &info);
  void SetSelfPowered(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetRemoteWakeup(const Napi::CallbackInfo &info);
  void SetRemoteWakeup(const Napi::CallbackInfo &info, const Napi::Value &value);

  // FT2232H extensions
  Napi::Value GetPullDownEnableH(const Napi::CallbackInfo &info);
  void SetPullDownEnableH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetSerNumEnableH(const Napi::CallbackInfo &info);
  void SetSerNumEnableH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetACSlowSlewH(const Napi::CallbackInfo &info);
  void SetACSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetACSchmittInputH(const Napi::CallbackInfo &info);
  void SetACSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetACDriveCurrentH(const Napi::CallbackInfo &info);
  void SetACDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetADSlowSlewH(const Napi::CallbackInfo &info);
  void SetADSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetADSchmittInputH(const Napi::CallbackInfo &info);
  void SetADSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetADDriveCurrentH(const Napi::CallbackInfo &info);
  void SetADDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus0H(const Napi::CallbackInfo &info);
  void SetCbus0H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus1H(const Napi::CallbackInfo &info);
  void SetCbus1H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus2H(const Napi::CallbackInfo &info);
  void SetCbus2H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus3H(const Napi::CallbackInfo &info);
  void SetCbus3H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus4H(const Napi::CallbackInfo &info);
  void SetCbus4H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus5H(const Napi::CallbackInfo &info);
  void SetCbus5H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus6H(const Napi::CallbackInfo &info);
  void SetCbus6H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus7H(const Napi::CallbackInfo &info);
  void SetCbus7H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus8H(const Napi::CallbackInfo &info);
  void SetCbus8H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetCbus9H(const Napi::CallbackInfo &info);
  void SetCbus9H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetIsFifoH(const Napi::CallbackInfo &info);
  void SetIsFifoH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetIsFifoTarH(const Napi::CallbackInfo &info);
  void SetIsFifoTarH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetIsFastSerH(const Napi::CallbackInfo &info);
  void SetIsFastSerH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetIsFT1248H(const Napi::CallbackInfo &info);
  void SetIsFT1248H(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetFT1248CpolH(const Napi::CallbackInfo &info);
  void SetFT1248CpolH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetFT1248LsbH(const Napi::CallbackInfo &info);
  void SetFT1248LsbH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetFT1248FlowControlH(const Napi::CallbackInfo &info);
  void SetFT1248FlowControlH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetIsVCPH(const Napi::CallbackInfo &info);
  void SetIsVCPH(const Napi::CallbackInfo &info, const Napi::Value &value);
  Napi::Value GetPowerSaveEnableH(const Napi::CallbackInfo &info);
  void SetPowerSaveEnableH(const Napi::CallbackInfo &info, const Napi::Value &value);

  inline static void StrCopy(Napi::String src, char *dst, int maxLenght);
};

Napi::FunctionReference FtProgramDataWrapper::constructor;

Napi::Object FtProgramDataWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(
      env,
      "FT_PROGRAM_DATA",
      {InstanceAccessor("signature1", &FtProgramDataWrapper::GetSignature1, &FtProgramDataWrapper::SetSignature1),
       InstanceAccessor("signature2", &FtProgramDataWrapper::GetSignature2, &FtProgramDataWrapper::SetSignature2),
       InstanceAccessor("version", &FtProgramDataWrapper::GetVersion, &FtProgramDataWrapper::SetVersion),
       InstanceAccessor("vendorId", &FtProgramDataWrapper::GetVendorId, &FtProgramDataWrapper::SetVendorId),
       InstanceAccessor("productId", &FtProgramDataWrapper::GetProductId, &FtProgramDataWrapper::SetProductId),

       InstanceAccessor("manufacturer", &FtProgramDataWrapper::GetManufacturer, &FtProgramDataWrapper::SetManufacturer),
       InstanceAccessor("manufacturerId", &FtProgramDataWrapper::GetManufacturerId, &FtProgramDataWrapper::SetManufacturerId),
       InstanceAccessor("description", &FtProgramDataWrapper::GetDescription, &FtProgramDataWrapper::SetDescription),
       InstanceAccessor("serialNumber", &FtProgramDataWrapper::GetSerialNumber, &FtProgramDataWrapper::SetSerialNumber),

       InstanceAccessor("maxPower", &FtProgramDataWrapper::GetMaxPower, &FtProgramDataWrapper::SetMaxPower),
       InstanceAccessor("pnp", &FtProgramDataWrapper::GetPnP, &FtProgramDataWrapper::SetPnP),
       InstanceAccessor("selfPowered", &FtProgramDataWrapper::GetSelfPowered, &FtProgramDataWrapper::SetSelfPowered),
       InstanceAccessor("remoteWakeup", &FtProgramDataWrapper::GetRemoteWakeup, &FtProgramDataWrapper::SetRemoteWakeup),

       InstanceAccessor("pullDownEnableH", &FtProgramDataWrapper::GetPullDownEnableH, &FtProgramDataWrapper::SetPullDownEnableH),
       InstanceAccessor("serNumEnableH", &FtProgramDataWrapper::GetSerNumEnableH, &FtProgramDataWrapper::SetSerNumEnableH),
       InstanceAccessor("acSlowSlewH", &FtProgramDataWrapper::GetACSlowSlewH, &FtProgramDataWrapper::SetACSlowSlewH),
       InstanceAccessor("acSchmittInputH", &FtProgramDataWrapper::GetACSchmittInputH, &FtProgramDataWrapper::SetACSchmittInputH),
       InstanceAccessor("acDriveCurrentH", &FtProgramDataWrapper::GetACDriveCurrentH, &FtProgramDataWrapper::SetACDriveCurrentH),
       InstanceAccessor("adSlowSlewH", &FtProgramDataWrapper::GetADSlowSlewH, &FtProgramDataWrapper::SetADSlowSlewH),
       InstanceAccessor("adSchmittInputH", &FtProgramDataWrapper::GetADSchmittInputH, &FtProgramDataWrapper::SetADSchmittInputH),
       InstanceAccessor("adDriveCurrentH", &FtProgramDataWrapper::GetADDriveCurrentH, &FtProgramDataWrapper::SetADDriveCurrentH),
       InstanceAccessor("cbus0H", &FtProgramDataWrapper::GetCbus0H, &FtProgramDataWrapper::SetCbus0H),
       InstanceAccessor("cbus1H", &FtProgramDataWrapper::GetCbus1H, &FtProgramDataWrapper::SetCbus1H),
       InstanceAccessor("cbus2H", &FtProgramDataWrapper::GetCbus2H, &FtProgramDataWrapper::SetCbus2H),
       InstanceAccessor("cbus3H", &FtProgramDataWrapper::GetCbus3H, &FtProgramDataWrapper::SetCbus3H),
       InstanceAccessor("cbus4H", &FtProgramDataWrapper::GetCbus4H, &FtProgramDataWrapper::SetCbus4H),
       InstanceAccessor("cbus5H", &FtProgramDataWrapper::GetCbus5H, &FtProgramDataWrapper::SetCbus5H),
       InstanceAccessor("cbus6H", &FtProgramDataWrapper::GetCbus6H, &FtProgramDataWrapper::SetCbus6H),
       InstanceAccessor("cbus7H", &FtProgramDataWrapper::GetCbus7H, &FtProgramDataWrapper::SetCbus7H),
       InstanceAccessor("cbus8H", &FtProgramDataWrapper::GetCbus8H, &FtProgramDataWrapper::SetCbus8H),
       InstanceAccessor("cbus9H", &FtProgramDataWrapper::GetCbus9H, &FtProgramDataWrapper::SetCbus9H),
       InstanceAccessor("isFifoH", &FtProgramDataWrapper::GetIsFifoH, &FtProgramDataWrapper::SetIsFifoH),
       InstanceAccessor("isFifoTarH", &FtProgramDataWrapper::GetIsFifoTarH, &FtProgramDataWrapper::SetIsFifoTarH),
       InstanceAccessor("isFastSerH", &FtProgramDataWrapper::GetIsFastSerH, &FtProgramDataWrapper::SetIsFastSerH),
       InstanceAccessor("isFT1248H", &FtProgramDataWrapper::GetIsFT1248H, &FtProgramDataWrapper::SetIsFT1248H),
       InstanceAccessor("ft1248CpolH", &FtProgramDataWrapper::GetFT1248CpolH, &FtProgramDataWrapper::SetFT1248CpolH),
       InstanceAccessor("ft1248LsbH", &FtProgramDataWrapper::GetFT1248LsbH, &FtProgramDataWrapper::SetFT1248LsbH),
       InstanceAccessor("ft1248FlowControlH", &FtProgramDataWrapper::GetFT1248FlowControlH, &FtProgramDataWrapper::SetFT1248FlowControlH),
       InstanceAccessor("isVCPH", &FtProgramDataWrapper::GetIsVCPH, &FtProgramDataWrapper::SetIsVCPH),
       InstanceAccessor("powerSaveEnableH", &FtProgramDataWrapper::GetPowerSaveEnableH, &FtProgramDataWrapper::SetPowerSaveEnableH)});
  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("FT_PROGRAM_DATA", func);
  return exports;
}

Napi::Object FtProgramDataWrapper::NewInstance(Napi::Env env, FT_HANDLE ftHandle)
{
  Napi::EscapableHandleScope scope(env);
  Napi::Object obj = constructor.New({});
  return scope.Escape(napi_value(obj)).ToObject();
}

PFT_PROGRAM_DATA FtProgramDataWrapper::GetData(Napi::Value value)
{
  FtProgramDataWrapper *wrapper = Napi::ObjectWrap<FtProgramDataWrapper>::Unwrap(value.As<Napi::Object>());
  return wrapper->GetData();
}

FtProgramDataWrapper::FtProgramDataWrapper(const Napi::CallbackInfo &info) : Napi::ObjectWrap<FtProgramDataWrapper>(info)
{
  ftData.Manufacturer = manufacturer;
  ftData.ManufacturerId = manufacturerId;
  ftData.Description = description;
  ftData.SerialNumber = serialNumber;
}

PFT_PROGRAM_DATA FtProgramDataWrapper::GetData()
{
  return &ftData;
}

Napi::Value FtProgramDataWrapper::GetSignature1(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Signature1);
}

void FtProgramDataWrapper::SetSignature1(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Signature1 = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetSignature2(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Signature2);
}

void FtProgramDataWrapper::SetSignature2(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Signature2 = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetVersion(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Version);
}

void FtProgramDataWrapper::SetVersion(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Version = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetVendorId(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.VendorId);
}

void FtProgramDataWrapper::SetVendorId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.VendorId = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetProductId(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.ProductId);
}

void FtProgramDataWrapper::SetProductId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.ProductId = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetManufacturer(const Napi::CallbackInfo &info)
{
  return Napi::String::New(info.Env(), manufacturer);
}

void FtProgramDataWrapper::SetManufacturer(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsString())
  {
    StrCopy(value.As<Napi::String>(), manufacturer, 32);
  }
  else
  {
    Napi::TypeError::New(info.Env(), "String expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetManufacturerId(const Napi::CallbackInfo &info)
{
  return Napi::String::New(info.Env(), manufacturerId);
}

void FtProgramDataWrapper::SetManufacturerId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsString())
  {
    StrCopy(value.As<Napi::String>(), manufacturerId, 16);
  }
  else
  {
    Napi::TypeError::New(info.Env(), "String expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetDescription(const Napi::CallbackInfo &info)
{
  return Napi::String::New(info.Env(), description);
}

void FtProgramDataWrapper::SetDescription(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsString())
  {
    StrCopy(value.As<Napi::String>(), description, 64);
  }
  else
  {
    Napi::TypeError::New(info.Env(), "String expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetSerialNumber(const Napi::CallbackInfo &info)
{
  return Napi::String::New(info.Env(), serialNumber);
}

void FtProgramDataWrapper::SetSerialNumber(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsString())
  {
    StrCopy(value.As<Napi::String>(), serialNumber, 16);
  }
  else
  {
    Napi::TypeError::New(info.Env(), "String expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetMaxPower(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.MaxPower);
}

void FtProgramDataWrapper::SetMaxPower(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.MaxPower = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetPnP(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.PnP);
}

void FtProgramDataWrapper::SetPnP(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.PnP = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetSelfPowered(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.SelfPowered);
}

void FtProgramDataWrapper::SetSelfPowered(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.SelfPowered = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetRemoteWakeup(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.RemoteWakeup);
}

void FtProgramDataWrapper::SetRemoteWakeup(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.RemoteWakeup = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetPullDownEnableH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.PullDownEnableH);
}

void FtProgramDataWrapper::SetPullDownEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.PullDownEnableH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetSerNumEnableH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.SerNumEnableH);
}

void FtProgramDataWrapper::SetSerNumEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.SerNumEnableH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetACSlowSlewH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.ACSlowSlewH);
}

void FtProgramDataWrapper::SetACSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.ACSlowSlewH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetACSchmittInputH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.ACSchmittInputH);
}

void FtProgramDataWrapper::SetACSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.ACSchmittInputH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetACDriveCurrentH(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.ACDriveCurrentH);
}

void FtProgramDataWrapper::SetACDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.ACDriveCurrentH = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetADSlowSlewH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.ADSlowSlewH);
}

void FtProgramDataWrapper::SetADSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.ADSlowSlewH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetADSchmittInputH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.ADSchmittInputH);
}

void FtProgramDataWrapper::SetADSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.ADSchmittInputH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetADDriveCurrentH(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.ADDriveCurrentH);
}

void FtProgramDataWrapper::SetADDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.ADDriveCurrentH = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus0H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus0H);
}

void FtProgramDataWrapper::SetCbus0H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus0H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus1H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus1H);
}

void FtProgramDataWrapper::SetCbus1H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus1H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus2H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus2H);
}

void FtProgramDataWrapper::SetCbus2H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus2H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus3H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus3H);
}

void FtProgramDataWrapper::SetCbus3H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus3H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus4H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus4H);
}

void FtProgramDataWrapper::SetCbus4H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus4H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus5H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus5H);
}

void FtProgramDataWrapper::SetCbus5H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus5H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus6H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus6H);
}

void FtProgramDataWrapper::SetCbus6H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus6H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus7H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus7H);
}

void FtProgramDataWrapper::SetCbus7H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus7H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus8H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus8H);
}

void FtProgramDataWrapper::SetCbus8H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus8H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetCbus9H(const Napi::CallbackInfo &info)
{
  return Napi::Number::New(info.Env(), ftData.Cbus9H);
}

void FtProgramDataWrapper::SetCbus9H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsNumber())
  {
    ftData.Cbus9H = value.As<Napi::Number>().Uint32Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetIsFifoH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.IsFifoH);
}

void FtProgramDataWrapper::SetIsFifoH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.IsFifoH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetIsFifoTarH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.IsFifoTarH);
}

void FtProgramDataWrapper::SetIsFifoTarH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.IsFifoTarH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetIsFastSerH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.IsFastSerH);
}

void FtProgramDataWrapper::SetIsFastSerH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.IsFastSerH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetIsFT1248H(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.IsFT1248H);
}

void FtProgramDataWrapper::SetIsFT1248H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.IsFT1248H = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetFT1248CpolH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.FT1248CpolH);
}

void FtProgramDataWrapper::SetFT1248CpolH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.FT1248CpolH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetFT1248LsbH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.FT1248LsbH);
}

void FtProgramDataWrapper::SetFT1248LsbH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.FT1248LsbH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetFT1248FlowControlH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.FT1248FlowControlH);
}

void FtProgramDataWrapper::SetFT1248FlowControlH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.FT1248FlowControlH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetIsVCPH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.IsVCPH);
}

void FtProgramDataWrapper::SetIsVCPH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.IsVCPH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

Napi::Value FtProgramDataWrapper::GetPowerSaveEnableH(const Napi::CallbackInfo &info)
{
  return Napi::Boolean::New(info.Env(), ftData.PowerSaveEnableH);
}

void FtProgramDataWrapper::SetPowerSaveEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  if (value.IsBoolean())
  {
    ftData.PowerSaveEnableH = value.As<Napi::Boolean>().Value();
  }
  else
  {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
}

void FtProgramDataWrapper::StrCopy(Napi::String src, char *dst, int maxLenght)
{
  std::string str = src.As<Napi::String>().Utf8Value();
  int length = str.length();
  length = length < maxLenght ? length : maxLenght - 1;
  str.copy(dst, length);
  dst[length] = '\0';
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
  Napi::Object deviceInfoNode = Napi::Object::New(env);
  Napi::Value nFtHandler = ftHandle == nullptr
                               ? env.Null()
                               : FtHandlerWrapper::NewInstance(env, ftHandle);
  deviceInfoNode.Set("flags", flags);
  deviceInfoNode.Set("type", type);
  deviceInfoNode.Set("id", id);
  deviceInfoNode.Set("locId", locId);
  deviceInfoNode.Set("serialNumber", serialNumber);
  deviceInfoNode.Set("description", description);
  deviceInfoNode.Set("ftHandle", nFtHandler);
  result.Set("deviceInfoNode", deviceInfoNode);
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
  exports.Set("setDataCharacteristics", Napi::Function::New(env, SetDataCharacteristicsOp::Invoke));
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
  DWORD deviceId;
  char serialNumber[16];
  char description[64];
  inline static Napi::Object CreateResult(
      Napi::Env env,
      FT_STATUS ftStatus,
      FT_DEVICE ftDevice,
      DWORD deviceId,
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
  DWORD deviceId;
  char serialNumber[16];
  char description[64];
  FT_STATUS ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceId, serialNumber, description, nullptr);
  return CreateResult(info.Env(), ftStatus, ftDevice, deviceId, serialNumber, description);
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
  ftStatus = FT_GetDeviceInfo(ftHandle, &ftDevice, &deviceId, serialNumber, description, nullptr);
}

void GetDeviceInfoOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateResult(Env(), ftStatus, ftDevice, deviceId, serialNumber, description));
}

Napi::Object GetDeviceInfoOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus,
    FT_DEVICE ftDevice,
    DWORD deviceId,
    char *serialNumber,
    char *description)
{
  Napi::Object result = CreateFtResultObject(env, ftStatus);
  result.Set("ftDevice", ftDevice);
  result.Set("deviceId", deviceId);
  result.Set("serialNumber", serialNumber);
  result.Set("description", description);
  return result;
}

///////////////////////////////////////////////////////////////////////////////
// EE_ReadOp class
////////////////////////////////////////////////////////////////////////////////

class EeReadOp : public BaseFtdiOp
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object InvokeSync(const Napi::CallbackInfo &info);
  static Napi::Promise Invoke(const Napi::CallbackInfo &info);
  EeReadOp(Napi::Env env, FT_HANDLE ftHandle, PFT_PROGRAM_DATA pftData);
  void Execute();
  void OnOK();

private:
  FT_HANDLE ftHandle;
  PFT_PROGRAM_DATA pftData;
};

Napi::Object EeReadOp::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("eeReadSync", Napi::Function::New(env, EeReadOp::InvokeSync));
  exports.Set("eeRead", Napi::Function::New(env, EeReadOp::Invoke));
  return exports;
}

Napi::Object EeReadOp::InvokeSync(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  PFT_PROGRAM_DATA pftData = FtProgramDataWrapper::GetData(info[1]);
  FT_STATUS ftStatus = FT_EE_Read(ftHandle, pftData);
  return CreateFtResultObject(info.Env(), ftStatus);
}

Napi::Promise EeReadOp::Invoke(const Napi::CallbackInfo &info)
{
  FT_HANDLE ftHandle = FtHandlerWrapper::GetFtHandler(info[0]);
  PFT_PROGRAM_DATA pftData = FtProgramDataWrapper::GetData(info[1]);
  auto *operation = new EeReadOp(info.Env(), ftHandle, pftData);
  operation->Queue();
  return operation->Promise();
}

EeReadOp::EeReadOp(Napi::Env env, FT_HANDLE ftHandle, PFT_PROGRAM_DATA pftData) : BaseFtdiOp(env), ftHandle(ftHandle), pftData(pftData) {}

void EeReadOp::Execute()
{
  ftStatus = FT_EE_Read(ftHandle, pftData);
}

void EeReadOp::OnOK()
{
  Napi::HandleScope scope(Env());
  deferred.Resolve(CreateFtResultObject(Env(), ftStatus));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  FtHandlerWrapper::Init(env, exports);
  FtProgramDataWrapper::Init(env, exports);
  CreateDeviceInfoListOp::Init(env, exports);
  GetDeviceInfoDetailOp::Init(env, exports);
  OpenOp::Init(env, exports);
  OpenExOp::Init(env, exports);
  CloseOp::Init(env, exports);
  SetDataCharacteristicsOp::Init(env, exports);
  SetFlowControlOp::Init(env, exports);
  SetBaudRateOp::Init(env, exports);
  GetDeviceInfoOp::Init(env, exports);
  EeReadOp::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)
