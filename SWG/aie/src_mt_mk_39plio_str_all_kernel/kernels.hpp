#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <adf/stream/types.h>

void aie_swg_str_kernel(input_stream_int32* __restrict in0, input_stream_int32* __restrict in1, output_stream_int32* __restrict out);

void aie_swg_str_master(input_stream_int32* __restrict in0, input_stream_int32* __restrict in1, output_stream_int32* __restrict out0, output_stream_int32* __restrict out1);

#endif /**********__KERNELS_H__**********/
