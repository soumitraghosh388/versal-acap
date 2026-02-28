// Copyright Soumitra Ghosh, IIIT Hyderabad, India, 2025
//
// SPDX-License-Identifier: MIT
#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define N 39
#define NK 9
#define READ_LEN 128
#define REF_LEN 128
#define NREF 10
#define QUERY_PKTS READ_LEN/16
#define REF_PKT_LEN REF_LEN/16
#define REF_PKTS (NK+1)*NREF*REF_PKT_LEN

extern "C" {
void pl_mm2s(
    const ap_int<32>* mem_query,
    const ap_int<32>* mem_ref_1,
    const ap_int<32>* mem_ref_2,
    const ap_int<32>* mem_ref_3,
    const ap_int<32>* mem_ref_4,
    const ap_int<32>* mem_ref_5,
    const ap_int<32>* mem_ref_6,
    const ap_int<32>* mem_ref_7,
    const ap_int<32>* mem_ref_8,
    const ap_int<32>* mem_ref_9,
	const ap_int<32>* mem_ref_10,
	const ap_int<32>* mem_ref_11,
	const ap_int<32>* mem_ref_12,
	const ap_int<32>* mem_ref_13,
	const ap_int<32>* mem_ref_14,
	const ap_int<32>* mem_ref_15,
	const ap_int<32>* mem_ref_16,
	const ap_int<32>* mem_ref_17,
	const ap_int<32>* mem_ref_18,
    const ap_int<32>* mem_ref_19,
    const ap_int<32>* mem_ref_20,
    const ap_int<32>* mem_ref_21,
    const ap_int<32>* mem_ref_22,
    const ap_int<32>* mem_ref_23,
    const ap_int<32>* mem_ref_24,
    const ap_int<32>* mem_ref_25,
    const ap_int<32>* mem_ref_26,
    const ap_int<32>* mem_ref_27,
	const ap_int<32>* mem_ref_28,
	const ap_int<32>* mem_ref_29,
	const ap_int<32>* mem_ref_30,
	const ap_int<32>* mem_ref_31,
	const ap_int<32>* mem_ref_32,
	const ap_int<32>* mem_ref_33,
	const ap_int<32>* mem_ref_34,
	const ap_int<32>* mem_ref_35,
	const ap_int<32>* mem_ref_36,
	const ap_int<32>* mem_ref_37,
	const ap_int<32>* mem_ref_38,
	const ap_int<32>* mem_ref_39,

    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_0,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_1,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_2,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_3,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_4,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_5,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_6,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_7,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_8,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_9,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_10,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_11,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_12,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_13,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_14,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_15,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_16,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_17,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_18,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_19,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_20,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_21,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_22,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_23,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_24,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_25,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_26,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_27,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_28,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_29,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_30,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_31,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_32,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_33,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_34,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_35,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_36,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_37,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_query_38,

    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_0,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_1,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_2,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_3,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_4,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_5,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_6,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_7,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_8,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_9,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_10,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_11,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_12,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_13,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_14,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_15,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_16,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_17,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_18,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_19,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_20,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_21,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_22,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_23,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_24,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_25,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_26,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_27,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_28,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_29,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_30,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_31,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_32,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_33,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_34,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_35,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_36,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_37,
    hls::stream<ap_axis<32, 0, 0, 0> >& out_ref_38) {
    //hls::print("sizeof(int) : %d, ", sizeof(int));
#pragma HLS INTERFACE m_axi port=mem_query offset=slave bundle=gmem0 depth=QUERY_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_1   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_2   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_3   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_4   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_5   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_6   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_7   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_8   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_9   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_10   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_11   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_12   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_13   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_14   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_15   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_16   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_17   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_18   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_19   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_20   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_21   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_22   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_23   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_24   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_25   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_26   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_27   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_28   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_29   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_30   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_31   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_32   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_33   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_34   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_35   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_36   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_37   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_38   offset=slave bundle=gmem1 depth=REF_PKTS
#pragma HLS INTERFACE m_axi port=mem_ref_39   offset=slave bundle=gmem1 depth=REF_PKTS

#pragma HLS INTERFACE axis port=out_query_0
#pragma HLS INTERFACE axis port=out_query_1
#pragma HLS INTERFACE axis port=out_query_2
#pragma HLS INTERFACE axis port=out_query_3
#pragma HLS INTERFACE axis port=out_query_4
#pragma HLS INTERFACE axis port=out_query_5
#pragma HLS INTERFACE axis port=out_query_6
#pragma HLS INTERFACE axis port=out_query_7
#pragma HLS INTERFACE axis port=out_query_8
#pragma HLS INTERFACE axis port=out_query_9
#pragma HLS INTERFACE axis port=out_query_10
#pragma HLS INTERFACE axis port=out_query_11
#pragma HLS INTERFACE axis port=out_query_12
#pragma HLS INTERFACE axis port=out_query_13
#pragma HLS INTERFACE axis port=out_query_14
#pragma HLS INTERFACE axis port=out_query_15
#pragma HLS INTERFACE axis port=out_query_16
#pragma HLS INTERFACE axis port=out_query_17
#pragma HLS INTERFACE axis port=out_query_18
#pragma HLS INTERFACE axis port=out_query_19
#pragma HLS INTERFACE axis port=out_query_20
#pragma HLS INTERFACE axis port=out_query_21
#pragma HLS INTERFACE axis port=out_query_22
#pragma HLS INTERFACE axis port=out_query_23
#pragma HLS INTERFACE axis port=out_query_24
#pragma HLS INTERFACE axis port=out_query_25
#pragma HLS INTERFACE axis port=out_query_26
#pragma HLS INTERFACE axis port=out_query_27
#pragma HLS INTERFACE axis port=out_query_28
#pragma HLS INTERFACE axis port=out_query_29
#pragma HLS INTERFACE axis port=out_query_30
#pragma HLS INTERFACE axis port=out_query_31
#pragma HLS INTERFACE axis port=out_query_32
#pragma HLS INTERFACE axis port=out_query_33
#pragma HLS INTERFACE axis port=out_query_34
#pragma HLS INTERFACE axis port=out_query_35
#pragma HLS INTERFACE axis port=out_query_36
#pragma HLS INTERFACE axis port=out_query_37
#pragma HLS INTERFACE axis port=out_query_38

#pragma HLS INTERFACE axis port=out_ref_0
#pragma HLS INTERFACE axis port=out_ref_1
#pragma HLS INTERFACE axis port=out_ref_2
#pragma HLS INTERFACE axis port=out_ref_3
#pragma HLS INTERFACE axis port=out_ref_4
#pragma HLS INTERFACE axis port=out_ref_5
#pragma HLS INTERFACE axis port=out_ref_6
#pragma HLS INTERFACE axis port=out_ref_7
#pragma HLS INTERFACE axis port=out_ref_8
#pragma HLS INTERFACE axis port=out_ref_9
#pragma HLS INTERFACE axis port=out_ref_10
#pragma HLS INTERFACE axis port=out_ref_11
#pragma HLS INTERFACE axis port=out_ref_12
#pragma HLS INTERFACE axis port=out_ref_13
#pragma HLS INTERFACE axis port=out_ref_14
#pragma HLS INTERFACE axis port=out_ref_15
#pragma HLS INTERFACE axis port=out_ref_16
#pragma HLS INTERFACE axis port=out_ref_17
#pragma HLS INTERFACE axis port=out_ref_18
#pragma HLS INTERFACE axis port=out_ref_19
#pragma HLS INTERFACE axis port=out_ref_20
#pragma HLS INTERFACE axis port=out_ref_21
#pragma HLS INTERFACE axis port=out_ref_22
#pragma HLS INTERFACE axis port=out_ref_23
#pragma HLS INTERFACE axis port=out_ref_24
#pragma HLS INTERFACE axis port=out_ref_25
#pragma HLS INTERFACE axis port=out_ref_26
#pragma HLS INTERFACE axis port=out_ref_27
#pragma HLS INTERFACE axis port=out_ref_28
#pragma HLS INTERFACE axis port=out_ref_29
#pragma HLS INTERFACE axis port=out_ref_30
#pragma HLS INTERFACE axis port=out_ref_31
#pragma HLS INTERFACE axis port=out_ref_32
#pragma HLS INTERFACE axis port=out_ref_33
#pragma HLS INTERFACE axis port=out_ref_34
#pragma HLS INTERFACE axis port=out_ref_35
#pragma HLS INTERFACE axis port=out_ref_36
#pragma HLS INTERFACE axis port=out_ref_37
#pragma HLS INTERFACE axis port=out_ref_38

#pragma HLS INTERFACE s_axilite port=mem_query bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_1 bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_2 bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_3 bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_4   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_5   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_6   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_7   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_8   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_9   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_10   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_11   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_12   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_13   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_14   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_15   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_16   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_17   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_18   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_19   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_20   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_21   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_22   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_23   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_24   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_25   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_26   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_27   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_28   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_29   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_30   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_31   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_32   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_33   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_34   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_35   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_36   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_37   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_38   bundle=control
#pragma HLS INTERFACE s_axilite port=mem_ref_39   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

	for (int j = 0; j < QUERY_PKTS; j++) {
		ap_axis<32, 0, 0, 0> x;
		x.data = mem_query[j];
		out_query_0.write(x);
		out_query_1.write(x);
		out_query_2.write(x);
		out_query_3.write(x);
		out_query_4.write(x);
		out_query_5.write(x);
		out_query_6.write(x);
		out_query_7.write(x);
		out_query_8.write(x);
		out_query_9.write(x);
		out_query_10.write(x);
		out_query_11.write(x);
		out_query_12.write(x);
		out_query_13.write(x);
		out_query_14.write(x);
		out_query_15.write(x);
		out_query_16.write(x);
		out_query_17.write(x);
		out_query_18.write(x);
		out_query_19.write(x);
		out_query_20.write(x);
		out_query_21.write(x);
		out_query_22.write(x);
		out_query_23.write(x);
		out_query_24.write(x);
		out_query_25.write(x);
		out_query_26.write(x);
		out_query_27.write(x);
		out_query_28.write(x);
		out_query_29.write(x);
		out_query_30.write(x);
		out_query_31.write(x);
		out_query_32.write(x);
		out_query_33.write(x);
		out_query_34.write(x);
		out_query_35.write(x);
		out_query_36.write(x);
		out_query_37.write(x);
		out_query_38.write(x);
	}

	for (int k = 0; k < REF_PKTS; k++) {
		ap_axis<32, 0, 0, 0> x;
		x.data = mem_ref_1[k];
		out_ref_0.write(x);
		x.data = mem_ref_2[k];
		out_ref_1.write(x);
		x.data = mem_ref_3[k];
		out_ref_2.write(x);
		x.data = mem_ref_4[k];
		out_ref_3.write(x);
		x.data = mem_ref_5[k];
		out_ref_4.write(x);
		x.data = mem_ref_6[k];
		out_ref_5.write(x);
		x.data = mem_ref_7[k];
		out_ref_6.write(x);
		x.data = mem_ref_8[k];
		out_ref_7.write(x);
		x.data = mem_ref_9[k];
		out_ref_8.write(x);
		x.data = mem_ref_10[k];
		out_ref_9.write(x);
		x.data = mem_ref_11[k];
		out_ref_10.write(x);
		x.data = mem_ref_12[k];
		out_ref_11.write(x);
		x.data = mem_ref_13[k];
		out_ref_12.write(x);
		x.data = mem_ref_14[k];
		out_ref_13.write(x);
		x.data = mem_ref_15[k];
		out_ref_14.write(x);
		x.data = mem_ref_16[k];
		out_ref_15.write(x);
		x.data = mem_ref_17[k];
		out_ref_16.write(x);
		x.data = mem_ref_18[k];
		out_ref_17.write(x);
		x.data = mem_ref_19[k];
		out_ref_18.write(x);
		x.data = mem_ref_20[k];
		out_ref_19.write(x);
		x.data = mem_ref_21[k];
		out_ref_20.write(x);
		x.data = mem_ref_22[k];
		out_ref_21.write(x);
		x.data = mem_ref_23[k];
		out_ref_22.write(x);
		x.data = mem_ref_24[k];
		out_ref_23.write(x);
		x.data = mem_ref_25[k];
		out_ref_24.write(x);
		x.data = mem_ref_26[k];
		out_ref_25.write(x);
		x.data = mem_ref_27[k];
		out_ref_26.write(x);
		x.data = mem_ref_28[k];
		out_ref_27.write(x);
		x.data = mem_ref_29[k];
		out_ref_28.write(x);
		x.data = mem_ref_30[k];
		out_ref_29.write(x);
		x.data = mem_ref_31[k];
		out_ref_30.write(x);
		x.data = mem_ref_32[k];
		out_ref_31.write(x);
		x.data = mem_ref_33[k];
		out_ref_32.write(x);
		x.data = mem_ref_34[k];
		out_ref_33.write(x);
		x.data = mem_ref_35[k];
		out_ref_34.write(x);
		x.data = mem_ref_36[k];
		out_ref_35.write(x);
		x.data = mem_ref_37[k];
		out_ref_36.write(x);
		x.data = mem_ref_38[k];
		out_ref_37.write(x);
		x.data = mem_ref_39[k];
		out_ref_38.write(x);
	}

	}
}
