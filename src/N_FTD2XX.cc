#include <napi.h>
#include <ftd2xx.h>
#if !_WIN32
#include <WinTypes.h>
#endif
#include "ft_program_data_wrapper.h"
#include "ft_base_op.h"
#include "ft_create_device_info_list_op.h"
#include "ft_get_device_info_detail_op.h"
#include "ft_open_op.h"
#include "ft_open_ex_op.h"
#include "ft_close_op.h"
#include "ft_set_data_characteristics_op.h"
#include "ft_set_flow_control_op.h"
#include "ft_set_baud_rate_op.h"
#include "ft_get_device_info_op.h"
#include "ft_ee_read_op.h"
#include "ft_write_op.h"
#include "ft_get_queue_status_op.h"
#include "ft_get_status_op.h"
#include "ft_read_op.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    FtProgramDataWrapper::Init(env, exports);
    FtCreateDeviceInfoListOp::Init(env, exports);
    FtGetDeviceInfoDetailOp::Init(env, exports);
    FtOpenOp::Init(env, exports);
    FtOpenExOp::Init(env, exports);
    FtCloseOp::Init(env, exports);
    FtSetDataCharacteristicsOp::Init(env, exports);
    FtSetFlowControlOp::Init(env, exports);
    FtSetBaudRateOp::Init(env, exports);
    FtGetDeviceInfoOp::Init(env, exports);
    FtEeReadOp::Init(env, exports);
    FtWriteOp::Init(env, exports);
    FtGetQueueStatusOp::Init(env, exports);
    FtGetStatusOp::Init(env, exports);
    FtReadOp::Init(env, exports);
    return exports;
}

NODE_API_MODULE(addon, Init)
