// Copyright Soumitra Ghosh, IIIT Hyderabad, India, 2025
//
// SPDX-License-Identifier: MIT
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <adf.h>
#include "kernels.hpp"
#include <string.h>

#define CONNECTION stream
#define N 39  // Number of parallel PLIO-AIE tile connections
#define NK 9  // Number of kernels excluding master
#define MAXROW 8

using namespace adf;

class simpleGraph : public graph {
private:
    kernel swg[(NK + 1) * N];

public:
    // Flattened input and output PLIOs
    input_plio p_s0_0, p_s0_1, p_s0_2, p_s0_3, p_s0_4, p_s0_5, p_s0_6, p_s0_7, p_s0_8, p_s0_9,
               p_s0_10, p_s0_11, p_s0_12, p_s0_13, p_s0_14, p_s0_15, p_s0_16, p_s0_17, p_s0_18, p_s0_19,
               p_s0_20, p_s0_21, p_s0_22, p_s0_23, p_s0_24, p_s0_25, p_s0_26, p_s0_27, p_s0_28, p_s0_29,
               p_s0_30, p_s0_31, p_s0_32, p_s0_33, p_s0_34, p_s0_35, p_s0_36, p_s0_37, p_s0_38;


    input_plio p_s1_0, p_s1_1, p_s1_2, p_s1_3, p_s1_4, p_s1_5, p_s1_6, p_s1_7, p_s1_8, p_s1_9,
               p_s1_10, p_s1_11, p_s1_12, p_s1_13, p_s1_14, p_s1_15, p_s1_16, p_s1_17, p_s1_18, p_s1_19,
               p_s1_20, p_s1_21, p_s1_22, p_s1_23, p_s1_24, p_s1_25, p_s1_26, p_s1_27, p_s1_28, p_s1_29,
               p_s1_30, p_s1_31, p_s1_32, p_s1_33, p_s1_34, p_s1_35, p_s1_36, p_s1_37, p_s1_38;

    output_plio p_s2_0, p_s2_1, p_s2_2, p_s2_3, p_s2_4, p_s2_5, p_s2_6, p_s2_7, p_s2_8, p_s2_9,
                p_s2_10, p_s2_11, p_s2_12, p_s2_13, p_s2_14, p_s2_15, p_s2_16, p_s2_17, p_s2_18, p_s2_19,
                p_s2_20, p_s2_21, p_s2_22, p_s2_23, p_s2_24, p_s2_25, p_s2_26, p_s2_27, p_s2_28, p_s2_29,
                p_s2_30, p_s2_31, p_s2_32, p_s2_33, p_s2_34, p_s2_35, p_s2_36, p_s2_37, p_s2_38;

    simpleGraph() {
        int ind_max = N;
        int col = 0;

        input_plio* p_s0_list[N] = {
            &p_s0_0, &p_s0_1, &p_s0_2, &p_s0_3, &p_s0_4, &p_s0_5, &p_s0_6, &p_s0_7, &p_s0_8, &p_s0_9,
            &p_s0_10, &p_s0_11, &p_s0_12, &p_s0_13, &p_s0_14, &p_s0_15, &p_s0_16, &p_s0_17, &p_s0_18, &p_s0_19,
            &p_s0_20, &p_s0_21, &p_s0_22, &p_s0_23, &p_s0_24, &p_s0_25, &p_s0_26, &p_s0_27, &p_s0_28, &p_s0_29,
            &p_s0_30, &p_s0_31, &p_s0_32, &p_s0_33, &p_s0_34, &p_s0_35, &p_s0_36, &p_s0_37, &p_s0_38 };

        input_plio* p_s1_list[N] = {
            &p_s1_0, &p_s1_1, &p_s1_2, &p_s1_3, &p_s1_4, &p_s1_5, &p_s1_6, &p_s1_7, &p_s1_8, &p_s1_9,
            &p_s1_10, &p_s1_11, &p_s1_12, &p_s1_13, &p_s1_14, &p_s1_15, &p_s1_16, &p_s1_17, &p_s1_18, &p_s1_19,
            &p_s1_20, &p_s1_21, &p_s1_22, &p_s1_23, &p_s1_24, &p_s1_25, &p_s1_26, &p_s1_27, &p_s1_28, &p_s1_29,
            &p_s1_30, &p_s1_31, &p_s1_32, &p_s1_33, &p_s1_34, &p_s1_35, &p_s1_36, &p_s1_37, &p_s1_38 };

        output_plio* p_s2_list[N] = {
            &p_s2_0, &p_s2_1, &p_s2_2, &p_s2_3, &p_s2_4, &p_s2_5, &p_s2_6, &p_s2_7, &p_s2_8, &p_s2_9,
            &p_s2_10, &p_s2_11, &p_s2_12, &p_s2_13, &p_s2_14, &p_s2_15, &p_s2_16, &p_s2_17, &p_s2_18, &p_s2_19,
            &p_s2_20, &p_s2_21, &p_s2_22, &p_s2_23, &p_s2_24, &p_s2_25, &p_s2_26, &p_s2_27, &p_s2_28, &p_s2_29,
            &p_s2_30, &p_s2_31, &p_s2_32, &p_s2_33, &p_s2_34, &p_s2_35, &p_s2_36, &p_s2_37, &p_s2_38 };

        for (int i = 0; i < N; i++) {
            char out_file_str[30];
            sprintf(out_file_str, "output%d", i);

            char p0_name[30], p1_name[30], p2_name[30];
            sprintf(p0_name, "StreamIn0_%d", i);
            sprintf(p1_name, "StreamIn1_%d", i);
            sprintf(p2_name, "StreamOut0_%d", i);

            char p1_file[40];
            sprintf(p1_file, "data/input_%d.seq", i + 1);
            *p_s0_list[i] = input_plio::create(p0_name, plio_32_bits, "data/input_0.seq");
            *p_s1_list[i] = input_plio::create(p1_name, plio_32_bits, p1_file);
            *p_s2_list[i] = output_plio::create(p2_name, plio_32_bits, out_file_str);

            swg[i] = kernel::create(aie_swg_str_master);
            source(swg[i]) = "swg_stream_master.cc";
            runtime<ratio>(swg[i]) = 1;
            col = (i / MAXROW) * 10;
            location<kernel>(swg[i]) = tile(col, i % MAXROW);

            for (int j = 1; j <= NK; j++) {
                swg[ind_max] = kernel::create(aie_swg_str_kernel);
                source(swg[ind_max]) = "swg_stream_kernel.cc";
                runtime<ratio>(swg[ind_max]) = 1;
                location<kernel>(swg[ind_max]) = tile(col + j, i % MAXROW);
                if (j == 1) {
                    connect<CONNECTION>(swg[i].out[0], swg[ind_max].in[0]);
                } else {
                    connect<CONNECTION>(swg[ind_max - 1].out[0], swg[ind_max].in[0]);
                }
                connect<CONNECTION>(swg[i].out[1], swg[ind_max].in[1]);
                if (j == NK) {
                    connect<CONNECTION>(swg[ind_max].out[0], (*p_s2_list[i]).in[0]);
                }
                ind_max++;
            }

            connect<CONNECTION>((*p_s0_list[i]).out[0], swg[i].in[0]);
            connect<CONNECTION>((*p_s1_list[i]).out[0], swg[i].in[1]);
        }
    }
};

#endif  // __GRAPH_H__
