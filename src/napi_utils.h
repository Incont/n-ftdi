#ifndef NAPI_UTILS_H_
#define NAPI_UTILS_H_

#include <napi.h>

inline bool ThrowTypeErrorIfFalse(bool value, Napi::Env env, const char *message)
{
    if (!value)
    {
        Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
    }
    return value;
}

inline void StrCopy(Napi::String src, char *dst)
{
    std::string str = src.As<Napi::String>().Utf8Value();
    int length = str.length();
    int maxLenght = sizeof(dst);
    length = length < maxLenght ? length : maxLenght - 1;
    str.copy(dst, length);
    dst[length] = '\0';
}

#endif // NAPI_UTILS_H_