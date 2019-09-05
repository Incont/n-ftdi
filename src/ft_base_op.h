#ifndef FT_BASE_OP_H_
#define FT_BASE_OP_H_

#include <napi.h>
#include <ftd2xx.h>

class FtBaseOp : public Napi::AsyncWorker
{
public:
    FtBaseOp(Napi::Env env) : Napi::AsyncWorker(env, "ftdi"), deferred(Napi::Promise::Deferred::New(env)) {}
    Napi::Promise Promise()
    {
        return deferred.Promise();
    }

protected:
    Napi::Promise::Deferred deferred;
    FT_STATUS ftStatus;
};

#endif // FT_BASE_OP_H_