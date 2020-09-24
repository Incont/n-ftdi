#include "ft_ex_program_device_description_op.h"

Napi::Object FtExProgrammDeviceDescriptionOp::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("programDeviceDescriptionSync", Napi::Function::New(env, FtExProgrammDeviceDescriptionOp::InvokeSync));
    exports.Set("programDeviceInfo", Napi::Function::New(env, FtExProgrammDeviceDescriptionOp::Invoke));
    return exports;
}

Napi::Object FtExProgrammDeviceDescriptionOp::InvokeSync(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    FT_PROGRAM_DATA eeData;
    FT_STATUS ftStatus = FT_EE_Read(ftHandle, &eeData);
    if (ftStatus != FT_OK)
    {
        return CreateResult(info.Env(), ftStatus);
    }
    char *description = strdup(info[1].As<Napi::String>().Utf8Value().c_str());
    eeData.Description = description;
    ftStatus = FT_EE_Program(ftHandle, &eeData);
    free(description);
    return CreateResult(info.Env(), ftStatus);
}

Napi::Promise FtExProgrammDeviceDescriptionOp::Invoke(const Napi::CallbackInfo &info)
{
    FT_HANDLE ftHandle = (FT_HANDLE)info[0].As<Napi::External<void>>().Data();
    std::string description = info[1].As<Napi::String>().Utf8Value();
    auto *operation = new FtExProgrammDeviceDescriptionOp(info.Env(), ftHandle, description);
    operation->Queue();
    return operation->Promise();
}

FtExProgrammDeviceDescriptionOp::FtExProgrammDeviceDescriptionOp(Napi::Env env, FT_HANDLE ftHandle, std::string description) : FtBaseOp(env)
{
    strcpy(this->description, description.c_str());
}

void FtExProgrammDeviceDescriptionOp::Execute()
{
    FT_PROGRAM_DATA eeData;
    ftStatus = FT_EE_Read(ftHandle, &eeData);
    if (ftStatus == FT_OK)
    {
        eeData.Description = description;
        ftStatus = FT_EE_Program(ftHandle, &eeData);
    }
}

void FtExProgrammDeviceDescriptionOp::OnOK()
{
    Napi::HandleScope scope(Env());
    deferred.Resolve(CreateResult(Env(), ftStatus));
}

Napi::Object FtExProgrammDeviceDescriptionOp::CreateResult(
    Napi::Env env,
    FT_STATUS ftStatus)
{
    Napi::Object result = Napi::Object::New(env);
    result.Set("ftStatus", ftStatus);
    return result;
}