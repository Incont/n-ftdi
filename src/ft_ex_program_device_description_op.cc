#include "ft_ex_program_device_description_op.h"

Napi::Object FtExProgramDeviceDescriptionOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("programDeviceDescriptionSync", Napi::Function::New(env, FtExProgramDeviceDescriptionOp::InvokeSync));
    exports.Set("programDeviceDescription", Napi::Function::New(env, FtExProgramDeviceDescriptionOp::Invoke));
    return exports;
}

Napi::Number FtExProgramDeviceDescriptionOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    char description[64];
    strcpy(description , info[1].As<Napi::String>().Utf8Value().c_str());
    FT_STATUS ftStatus = FtExProgramDeviceDescription(ftHandle, description);
    return Napi::Number::New(info.Env(), ftStatus);
}

Napi::Promise FtExProgramDeviceDescriptionOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    std::string description = info[1].As<Napi::String>().Utf8Value();
    auto *operation = new FtExProgramDeviceDescriptionOp(info.Env(), ftHandle, description);
    operation->Queue();
    return operation->Promise();
}

FtExProgramDeviceDescriptionOp::FtExProgramDeviceDescriptionOp(Napi::Env env, FT_HANDLE ftHandle, std::string description) : FtBaseOp(env), ftHandle(ftHandle)
{
    strcpy(this->description, description.c_str());
}

void FtExProgramDeviceDescriptionOp::Execute()
{
    ftStatus = FtExProgramDeviceDescription(ftHandle, description);
}

void FtExProgramDeviceDescriptionOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(Napi::Number::New(Env(), ftStatus));
}

FT_STATUS FtExProgramDeviceDescriptionOp::FtExProgramDeviceDescription(FT_HANDLE ftHandle, const char* description) {
    FT_PROGRAM_DATA ftData;
    char ManufacturerBuf[32];
    char ManufacturerIdBuf[16];
    char DescriptionBuf[64];
    char SerialNumberBuf[16];
    ftData.Signature1 = 0x00000000;
    ftData.Signature2 = 0xffffffff;
    ftData.Version = 0x00000005;
    ftData.Manufacturer = ManufacturerBuf;
    ftData.ManufacturerId = ManufacturerIdBuf;
    ftData.Description = DescriptionBuf;
    ftData.SerialNumber = SerialNumberBuf;
    FT_STATUS ftStatus = FT_EE_Read(ftHandle, &ftData);
    strcpy(ftData.Description , description);
    if (ftStatus != FT_OK)
    {
        return ftStatus;
    }
    ftStatus = FT_EE_Program(ftHandle, &ftData);
    return ftStatus;
}
