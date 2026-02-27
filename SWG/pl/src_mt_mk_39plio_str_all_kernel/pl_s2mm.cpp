#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define N 39
#define NK 9  // Number of kernels excluding master
#define NREF 10 // number of references used by each kernel
#define PACKET_LEN (NK+1)*NREF

extern "C" {
void pl_s2mm(
    ap_int<32>* mem_out,

    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_0,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_1,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_2,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_3,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_4,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_5,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_6,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_7,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_8,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_9,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_10,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_11,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_12,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_13,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_14,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_15,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_16,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_17,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_18,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_19,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_20,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_21,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_22,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_23,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_24,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_25,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_26,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_27,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_28,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_29,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_30,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_31,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_32,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_33,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_34,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_35,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_36,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_37,
    hls::stream<ap_axis<32, 0, 0, 0> >& in_data_38) {
#pragma HLS INTERFACE m_axi port=mem_out offset=slave bundle=gmem2 depth=N*PACKET_LEN

#pragma HLS INTERFACE axis port=in_data_0
#pragma HLS INTERFACE axis port=in_data_1
#pragma HLS INTERFACE axis port=in_data_2
#pragma HLS INTERFACE axis port=in_data_3
#pragma HLS INTERFACE axis port=in_data_4
#pragma HLS INTERFACE axis port=in_data_5
#pragma HLS INTERFACE axis port=in_data_6
#pragma HLS INTERFACE axis port=in_data_7
#pragma HLS INTERFACE axis port=in_data_8
#pragma HLS INTERFACE axis port=in_data_9
#pragma HLS INTERFACE axis port=in_data_10
#pragma HLS INTERFACE axis port=in_data_11
#pragma HLS INTERFACE axis port=in_data_12
#pragma HLS INTERFACE axis port=in_data_13
#pragma HLS INTERFACE axis port=in_data_14
#pragma HLS INTERFACE axis port=in_data_15
#pragma HLS INTERFACE axis port=in_data_16
#pragma HLS INTERFACE axis port=in_data_17
#pragma HLS INTERFACE axis port=in_data_18
#pragma HLS INTERFACE axis port=in_data_19
#pragma HLS INTERFACE axis port=in_data_20
#pragma HLS INTERFACE axis port=in_data_21
#pragma HLS INTERFACE axis port=in_data_22
#pragma HLS INTERFACE axis port=in_data_23
#pragma HLS INTERFACE axis port=in_data_24
#pragma HLS INTERFACE axis port=in_data_25
#pragma HLS INTERFACE axis port=in_data_26
#pragma HLS INTERFACE axis port=in_data_27
#pragma HLS INTERFACE axis port=in_data_28
#pragma HLS INTERFACE axis port=in_data_29
#pragma HLS INTERFACE axis port=in_data_30
#pragma HLS INTERFACE axis port=in_data_31
#pragma HLS INTERFACE axis port=in_data_32
#pragma HLS INTERFACE axis port=in_data_33
#pragma HLS INTERFACE axis port=in_data_34
#pragma HLS INTERFACE axis port=in_data_35
#pragma HLS INTERFACE axis port=in_data_36
#pragma HLS INTERFACE axis port=in_data_37
#pragma HLS INTERFACE axis port=in_data_38

#pragma HLS INTERFACE s_axilite port=mem_out bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    for (int j = 0; j < PACKET_LEN; j++) {
//#pragma HLS PIPELINE II=1
    	mem_out[j] = in_data_0.read().data;
        mem_out[1 * PACKET_LEN + j] = in_data_1.read().data;
        mem_out[2 * PACKET_LEN + j] = in_data_2.read().data;
        mem_out[3 * PACKET_LEN + j] = in_data_3.read().data;
        mem_out[4 * PACKET_LEN + j] = in_data_4.read().data;
        mem_out[5 * PACKET_LEN + j] = in_data_5.read().data;
        mem_out[6 * PACKET_LEN + j] = in_data_6.read().data;
        mem_out[7 * PACKET_LEN + j] = in_data_7.read().data;
        mem_out[8 * PACKET_LEN + j] = in_data_8.read().data;
        mem_out[9 * PACKET_LEN + j] = in_data_9.read().data;
        mem_out[10 * PACKET_LEN + j] = in_data_10.read().data;
        mem_out[11 * PACKET_LEN + j] = in_data_11.read().data;
        mem_out[12 * PACKET_LEN + j] = in_data_12.read().data;
        mem_out[13 * PACKET_LEN + j] = in_data_13.read().data;
        mem_out[14 * PACKET_LEN + j] = in_data_14.read().data;
        mem_out[15 * PACKET_LEN + j] = in_data_15.read().data;
        mem_out[16 * PACKET_LEN + j] = in_data_16.read().data;
        mem_out[17 * PACKET_LEN + j] = in_data_17.read().data;
        mem_out[18 * PACKET_LEN + j] = in_data_18.read().data;
        mem_out[19 * PACKET_LEN + j] = in_data_19.read().data;
        mem_out[20 * PACKET_LEN + j] = in_data_20.read().data;
        mem_out[21 * PACKET_LEN + j] = in_data_21.read().data;
        mem_out[22 * PACKET_LEN + j] = in_data_22.read().data;
        mem_out[23 * PACKET_LEN + j] = in_data_23.read().data;
        mem_out[24 * PACKET_LEN + j] = in_data_24.read().data;
        mem_out[25 * PACKET_LEN + j] = in_data_25.read().data;
        mem_out[26 * PACKET_LEN + j] = in_data_26.read().data;
        mem_out[27 * PACKET_LEN + j] = in_data_27.read().data;
        mem_out[28 * PACKET_LEN + j] = in_data_28.read().data;
        mem_out[29 * PACKET_LEN + j] = in_data_29.read().data;
        mem_out[30 * PACKET_LEN + j] = in_data_30.read().data;
        mem_out[31 * PACKET_LEN + j] = in_data_31.read().data;
        mem_out[32 * PACKET_LEN + j] = in_data_32.read().data;
        mem_out[33 * PACKET_LEN + j] = in_data_33.read().data;
        mem_out[34 * PACKET_LEN + j] = in_data_34.read().data;
        mem_out[35 * PACKET_LEN + j] = in_data_35.read().data;
        mem_out[36 * PACKET_LEN + j] = in_data_36.read().data;
        mem_out[37 * PACKET_LEN + j] = in_data_37.read().data;
        mem_out[38 * PACKET_LEN + j] = in_data_38.read().data;
    }
    while (!in_data_0.empty()) {
      in_data_0.read();
    }
    while (!in_data_1.empty()) {
      in_data_1.read();
    }
    while (!in_data_2.empty()) {
      in_data_2.read();
    }
    while (!in_data_3.empty()) {
      in_data_3.read();
    }
    while (!in_data_4.empty()) {
      in_data_4.read();
    }
    while (!in_data_5.empty()) {
      in_data_5.read();
    }
    while (!in_data_6.empty()) {
      in_data_6.read();
    }
    while (!in_data_7.empty()) {
      in_data_7.read();
    }
    while (!in_data_8.empty()) {
      in_data_8.read();
    }
    while (!in_data_9.empty()) {
      in_data_9.read();
    }
    while (!in_data_10.empty()) {
      in_data_10.read();
    }
    while (!in_data_11.empty()) {
      in_data_11.read();
    }
    while (!in_data_12.empty()) {
      in_data_12.read();
    }
    while (!in_data_13.empty()) {
      in_data_13.read();
    }
    while (!in_data_14.empty()) {
      in_data_14.read();
    }
    while (!in_data_15.empty()) {
      in_data_15.read();
    }
    while (!in_data_16.empty()) {
      in_data_16.read();
    }
    while (!in_data_17.empty()) {
      in_data_17.read();
    }
    while (!in_data_18.empty()) {
          in_data_18.read();
    }
	while (!in_data_19.empty()) {
	  in_data_19.read();
	}
	while (!in_data_20.empty()) {
	  in_data_20.read();
	}
	while (!in_data_21.empty()) {
	  in_data_21.read();
	}
	while (!in_data_22.empty()) {
	  in_data_22.read();
	}
	while (!in_data_23.empty()) {
	  in_data_23.read();
	}
	while (!in_data_24.empty()) {
	  in_data_24.read();
	}
	while (!in_data_25.empty()) {
	  in_data_25.read();
	}
	while (!in_data_26.empty()) {
	  in_data_26.read();
	}
	while (!in_data_27.empty()) {
	  in_data_27.read();
	}
	while (!in_data_28.empty()) {
	  in_data_28.read();
	}
	while (!in_data_29.empty()) {
	  in_data_29.read();
	}
	while (!in_data_30.empty()) {
	  in_data_30.read();
	}
	while (!in_data_31.empty()) {
	  in_data_31.read();
	}
	while (!in_data_32.empty()) {
	  in_data_32.read();
	}
	while (!in_data_33.empty()) {
	  in_data_33.read();
	}
	while (!in_data_34.empty()) {
	  in_data_34.read();
	}
	while (!in_data_35.empty()) {
	  in_data_35.read();
	}
	while (!in_data_36.empty()) {
	  in_data_36.read();
	}
	while (!in_data_37.empty()) {
	  in_data_37.read();
	}
	while (!in_data_38.empty()) {
	  in_data_38.read();
	}
    // Handle stream 0 separately (outside loop, like index 0)
//#pragma HLS PIPELINE II=1

}
}
