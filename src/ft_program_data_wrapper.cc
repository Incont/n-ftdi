#include "ft_program_data_wrapper.h"

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

         InstanceAccessor("useExtOsc", &FtProgramDataWrapper::GetUseExtOsc, &FtProgramDataWrapper::SetUseExtOsc),
         InstanceAccessor("highDriveIOs", &FtProgramDataWrapper::GetHighDriveIOs, &FtProgramDataWrapper::SetHighDriveIOs),
         InstanceAccessor("endpointSize", &FtProgramDataWrapper::GetEndpointSize, &FtProgramDataWrapper::SetEndpointSize),
         InstanceAccessor("pullDownEnableR", &FtProgramDataWrapper::GetPullDownEnableR, &FtProgramDataWrapper::SetPullDownEnableR),
         InstanceAccessor("serNumEnableR", &FtProgramDataWrapper::GetSerNumEnableR, &FtProgramDataWrapper::SetSerNumEnableR),
         InstanceAccessor("invertTXD", &FtProgramDataWrapper::GetInvertTXD, &FtProgramDataWrapper::SetInvertTXD),
         InstanceAccessor("invertRXD", &FtProgramDataWrapper::GetInvertRXD, &FtProgramDataWrapper::SetInvertRXD),
         InstanceAccessor("invertRTS", &FtProgramDataWrapper::GetInvertRTS, &FtProgramDataWrapper::SetInvertRTS),
         InstanceAccessor("invertCTS", &FtProgramDataWrapper::GetInvertCTS, &FtProgramDataWrapper::SetInvertCTS),
         InstanceAccessor("invertDTR", &FtProgramDataWrapper::GetInvertDTR, &FtProgramDataWrapper::SetInvertDTR),
         InstanceAccessor("invertDSR", &FtProgramDataWrapper::GetInvertDSR, &FtProgramDataWrapper::SetInvertDSR),
         InstanceAccessor("invertDCD", &FtProgramDataWrapper::GetInvertDCD, &FtProgramDataWrapper::SetInvertDCD),
         InstanceAccessor("invertRI", &FtProgramDataWrapper::GetInvertRI, &FtProgramDataWrapper::SetInvertRI),
         InstanceAccessor("cbus0", &FtProgramDataWrapper::GetCbus0, &FtProgramDataWrapper::SetCbus0),
         InstanceAccessor("cbus1", &FtProgramDataWrapper::GetCbus1, &FtProgramDataWrapper::SetCbus1),
         InstanceAccessor("cbus2", &FtProgramDataWrapper::GetCbus2, &FtProgramDataWrapper::SetCbus2),
         InstanceAccessor("cbus3", &FtProgramDataWrapper::GetCbus3, &FtProgramDataWrapper::SetCbus3),
         InstanceAccessor("cbus4", &FtProgramDataWrapper::GetCbus4, &FtProgramDataWrapper::SetCbus4),
         InstanceAccessor("rIsD2XX", &FtProgramDataWrapper::GetRIsD2XX, &FtProgramDataWrapper::SetRIsD2XX),

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
    FtProgramDataWrapper *wrapper = FtProgramDataWrapper::Unwrap(value.As<Napi::Object>());
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
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Signature1 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetSignature2(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Signature2);
}

void FtProgramDataWrapper::SetSignature2(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Signature2 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetVersion(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Version);
}

void FtProgramDataWrapper::SetVersion(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Version = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetVendorId(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.VendorId);
}

void FtProgramDataWrapper::SetVendorId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.VendorId = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetProductId(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.ProductId);
}

void FtProgramDataWrapper::SetProductId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.ProductId = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetManufacturer(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), manufacturer);
}

void FtProgramDataWrapper::SetManufacturer(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsString(), info.Env(), "String expected"))
    {
        StrCopy(value.As<Napi::String>(), manufacturer, 32);
    }
}

Napi::Value FtProgramDataWrapper::GetManufacturerId(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), manufacturerId);
}

void FtProgramDataWrapper::SetManufacturerId(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsString(), info.Env(), "String expected"))
    {
        StrCopy(value.As<Napi::String>(), manufacturerId, 16);
    }
}

Napi::Value FtProgramDataWrapper::GetDescription(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), description);
}

void FtProgramDataWrapper::SetDescription(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsString(), info.Env(), "String expected"))
    {
        StrCopy(value.As<Napi::String>(), description, 64);
    }
}

Napi::Value FtProgramDataWrapper::GetSerialNumber(const Napi::CallbackInfo &info)
{
    return Napi::String::New(info.Env(), serialNumber);
}

void FtProgramDataWrapper::SetSerialNumber(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsString(), info.Env(), "String expected"))
    {
        StrCopy(value.As<Napi::String>(), serialNumber, 16);
    }
}

Napi::Value FtProgramDataWrapper::GetMaxPower(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.MaxPower);
}

void FtProgramDataWrapper::SetMaxPower(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.MaxPower = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetPnP(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.PnP);
}

void FtProgramDataWrapper::SetPnP(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.PnP = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetSelfPowered(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.SelfPowered);
}

void FtProgramDataWrapper::SetSelfPowered(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.SelfPowered = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetRemoteWakeup(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.RemoteWakeup);
}

void FtProgramDataWrapper::SetRemoteWakeup(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.RemoteWakeup = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetUseExtOsc(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.UseExtOsc);
}

void FtProgramDataWrapper::SetUseExtOsc(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.UseExtOsc = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetHighDriveIOs(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.HighDriveIOs);
}

void FtProgramDataWrapper::SetHighDriveIOs(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.HighDriveIOs = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetEndpointSize(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.EndpointSize);
}

void FtProgramDataWrapper::SetEndpointSize(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.EndpointSize = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetPullDownEnableR(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.PullDownEnableR);
}

void FtProgramDataWrapper::SetPullDownEnableR(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.PullDownEnableR = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetSerNumEnableR(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.SerNumEnableR);
}

void FtProgramDataWrapper::SetSerNumEnableR(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.SerNumEnableR = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertTXD(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertTXD);
}

void FtProgramDataWrapper::SetInvertTXD(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertTXD = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertRXD(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertRXD);
}

void FtProgramDataWrapper::SetInvertRXD(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertRXD = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertRTS(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertRTS);
}

void FtProgramDataWrapper::SetInvertRTS(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertRTS = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertCTS(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertCTS);
}

void FtProgramDataWrapper::SetInvertCTS(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertCTS = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertDTR(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertDTR);
}

void FtProgramDataWrapper::SetInvertDTR(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertDTR = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertDSR(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertDSR);
}

void FtProgramDataWrapper::SetInvertDSR(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertDSR = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertDCD(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertDCD);
}

void FtProgramDataWrapper::SetInvertDCD(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertDCD = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetInvertRI(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.InvertRI);
}

void FtProgramDataWrapper::SetInvertRI(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.InvertRI = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus0(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus0);
}
void FtProgramDataWrapper::SetCbus0(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus0 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus1(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus1);
}

void FtProgramDataWrapper::SetCbus1(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus1 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus2(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus2);
}

void FtProgramDataWrapper::SetCbus2(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus2 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus3(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus3);
}

void FtProgramDataWrapper::SetCbus3(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus3 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus4(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus4);
}

void FtProgramDataWrapper::SetCbus4(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus4 = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetRIsD2XX(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.RIsD2XX);
}

void FtProgramDataWrapper::SetRIsD2XX(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.RIsD2XX = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetPullDownEnableH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.PullDownEnableH);
}

void FtProgramDataWrapper::SetPullDownEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.PullDownEnableH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetSerNumEnableH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.SerNumEnableH);
}

void FtProgramDataWrapper::SetSerNumEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.SerNumEnableH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetACSlowSlewH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.ACSlowSlewH);
}

void FtProgramDataWrapper::SetACSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.ACSlowSlewH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetACSchmittInputH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.ACSchmittInputH);
}

void FtProgramDataWrapper::SetACSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.ACSchmittInputH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetACDriveCurrentH(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.ACDriveCurrentH);
}

void FtProgramDataWrapper::SetACDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.ACDriveCurrentH = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetADSlowSlewH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.ADSlowSlewH);
}

void FtProgramDataWrapper::SetADSlowSlewH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.ADSlowSlewH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetADSchmittInputH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.ADSchmittInputH);
}

void FtProgramDataWrapper::SetADSchmittInputH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.ADSchmittInputH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetADDriveCurrentH(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.ADDriveCurrentH);
}

void FtProgramDataWrapper::SetADDriveCurrentH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.ADDriveCurrentH = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus0H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus0H);
}

void FtProgramDataWrapper::SetCbus0H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus0H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus1H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus1H);
}

void FtProgramDataWrapper::SetCbus1H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus1H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus2H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus2H);
}

void FtProgramDataWrapper::SetCbus2H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus2H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus3H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus3H);
}

void FtProgramDataWrapper::SetCbus3H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus3H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus4H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus4H);
}

void FtProgramDataWrapper::SetCbus4H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus4H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus5H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus5H);
}

void FtProgramDataWrapper::SetCbus5H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus5H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus6H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus6H);
}

void FtProgramDataWrapper::SetCbus6H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus6H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus7H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus7H);
}

void FtProgramDataWrapper::SetCbus7H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus7H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus8H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus8H);
}

void FtProgramDataWrapper::SetCbus8H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus8H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetCbus9H(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), ftData.Cbus9H);
}

void FtProgramDataWrapper::SetCbus9H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsNumber(), info.Env(), "Number expected"))
    {
        ftData.Cbus9H = value.As<Napi::Number>().Uint32Value();
    }
}

Napi::Value FtProgramDataWrapper::GetIsFifoH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.IsFifoH);
}

void FtProgramDataWrapper::SetIsFifoH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.IsFifoH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetIsFifoTarH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.IsFifoTarH);
}

void FtProgramDataWrapper::SetIsFifoTarH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.IsFifoTarH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetIsFastSerH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.IsFastSerH);
}

void FtProgramDataWrapper::SetIsFastSerH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.IsFastSerH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetIsFT1248H(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.IsFT1248H);
}

void FtProgramDataWrapper::SetIsFT1248H(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.IsFT1248H = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetFT1248CpolH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.FT1248CpolH);
}

void FtProgramDataWrapper::SetFT1248CpolH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.FT1248CpolH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetFT1248LsbH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.FT1248LsbH);
}

void FtProgramDataWrapper::SetFT1248LsbH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.FT1248LsbH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetFT1248FlowControlH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.FT1248FlowControlH);
}

void FtProgramDataWrapper::SetFT1248FlowControlH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.FT1248FlowControlH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetIsVCPH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.IsVCPH);
}

void FtProgramDataWrapper::SetIsVCPH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.IsVCPH = value.As<Napi::Boolean>().Value();
    }
}

Napi::Value FtProgramDataWrapper::GetPowerSaveEnableH(const Napi::CallbackInfo &info)
{
    return Napi::Boolean::New(info.Env(), ftData.PowerSaveEnableH);
}

void FtProgramDataWrapper::SetPowerSaveEnableH(const Napi::CallbackInfo &info, const Napi::Value &value)
{
    if (ThrowTypeErrorIfFalse(value.IsBoolean(), info.Env(), "Boolean expected"))
    {
        ftData.PowerSaveEnableH = value.As<Napi::Boolean>().Value();
    }
}
