// Copyright Soumitra Ghosh, IIIT Hyderabad, India, 2025
//
// SPDX-License-Identifier: MIT
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include "xrt.h"
#include "experimental/xrt_kernel.h"

#define REF_LEN 128 // length of reference sequence
#define READ_LEN 128 // length of query sequence
#define NREF 10
#define NK 9
#define N 39
#define QUERY_PKTS READ_LEN/16
#define REF_PKT_LEN REF_LEN/16
#define REF_PKTS (NK+1)*NREF*REF_PKT_LEN

int main(int argc, char** argv) {

    std::clock_t start;
    std::clock_t end;
    double h2d_duration, d2h_duration, kernel_duration;

    // Check input arguments
    if (argc < 2 || argc > 4) {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File> <#elements(optional)> <debug(optional)>" << std::endl;
        return EXIT_FAILURE;
    }
    unsigned int num_elements_0 = QUERY_PKTS;
    unsigned int num_elements_1 = REF_PKTS;
    unsigned int num_elements_2 = N*(NK+1)*NREF;

    // Get device index and download xclbin
    std::cout << "Open the device" << std::endl;
    auto device = xrt::device(0);
    std::string binaryFile = argv[1];
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    // Get reference to the kernels
    std::cout << "Get references to compute units" << std::endl;
    auto pl_mm2s_1 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_1}");
    auto pl_s2mm_1 = xrt::kernel(device, uuid, "pl_s2mm:{pl_s2mm_1}");

    // Allocating the input size of sizeIn to MM2S
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    size_t size_in_bytes_0 = sizeof(int32_t) * num_elements_0 ;
    size_t size_in_bytes_1 = sizeof(int32_t) * num_elements_1 ;
    size_t size_in_bytes_2 = sizeof(int32_t) * num_elements_2 ;
    auto in_buff_1 = xrt::bo(device, size_in_bytes_0, pl_mm2s_1.group_id(0));

    auto in_buff_2 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(1));
    auto in_buff_3 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(2));
    auto in_buff_4 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(3));
    auto in_buff_5 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(4));
    auto in_buff_6 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(5));
    auto in_buff_7 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(6));
    auto in_buff_8 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(7));
    auto in_buff_9 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(8));
    auto in_buff_10 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(9));
    auto in_buff_11 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(10));
    auto in_buff_12 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(11));
    auto in_buff_13 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(12));
    auto in_buff_14 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(13));
    auto in_buff_15 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(14));
    auto in_buff_16 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(15));
    auto in_buff_17 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(16));
    auto in_buff_18 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(17));
    auto in_buff_19 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(18));
    auto in_buff_20 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(19));
    auto in_buff_21 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(20));
    auto in_buff_22 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(21));
    auto in_buff_23 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(22));
    auto in_buff_24 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(23));
    auto in_buff_25 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(24));
    auto in_buff_26 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(25));
    auto in_buff_27 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(26));
    auto in_buff_28 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(27));
    auto in_buff_29 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(28));
    auto in_buff_30 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(29));
    auto in_buff_31 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(30));
    auto in_buff_32 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(31));
    auto in_buff_33 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(32));
    auto in_buff_34 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(33));
    auto in_buff_35 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(34));
    auto in_buff_36 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(35));
    auto in_buff_37 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(36));
    auto in_buff_38 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(37));
    auto in_buff_39 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(38));
    auto in_buff_40 = xrt::bo(device, size_in_bytes_1, pl_mm2s_1.group_id(39));

    auto out_buff_1 = xrt::bo(device, size_in_bytes_2, pl_s2mm_1.group_id(0));

    // Generate random data and write data to compute unit buffers
    auto *DataInput0 = new int32_t [num_elements_0];

    auto *DataInput1 = new int32_t [num_elements_1];
    auto *DataInput2 = new int32_t [num_elements_1];
    auto *DataInput3 = new int32_t [num_elements_1];
    auto *DataInput4 = new int32_t [num_elements_1];
    auto *DataInput5 = new int32_t [num_elements_1];
    auto *DataInput6 = new int32_t [num_elements_1];
    auto *DataInput7 = new int32_t [num_elements_1];
    auto *DataInput8 = new int32_t [num_elements_1];
    auto *DataInput9 = new int32_t [num_elements_1];
    auto *DataInput10 = new int32_t [num_elements_1];
    auto *DataInput11 = new int32_t [num_elements_1];
    auto *DataInput12 = new int32_t [num_elements_1];
    auto *DataInput13 = new int32_t [num_elements_1];
    auto *DataInput14 = new int32_t [num_elements_1];
    auto *DataInput15 = new int32_t [num_elements_1];
    auto *DataInput16 = new int32_t [num_elements_1];
    auto *DataInput17 = new int32_t [num_elements_1];
    auto *DataInput18 = new int32_t [num_elements_1];
    auto *DataInput19 = new int32_t [num_elements_1];
    auto *DataInput20 = new int32_t [num_elements_1];
    auto *DataInput21 = new int32_t [num_elements_1];
    auto *DataInput22 = new int32_t [num_elements_1];
    auto *DataInput23 = new int32_t [num_elements_1];
    auto *DataInput24 = new int32_t [num_elements_1];
    auto *DataInput25 = new int32_t [num_elements_1];
    auto *DataInput26 = new int32_t [num_elements_1];
    auto *DataInput27 = new int32_t [num_elements_1];
    auto *DataInput28 = new int32_t [num_elements_1];
    auto *DataInput29 = new int32_t [num_elements_1];
    auto *DataInput30 = new int32_t [num_elements_1];
    auto *DataInput31 = new int32_t [num_elements_1];
    auto *DataInput32 = new int32_t [num_elements_1];
    auto *DataInput33 = new int32_t [num_elements_1];
    auto *DataInput34 = new int32_t [num_elements_1];
    auto *DataInput35 = new int32_t [num_elements_1];
    auto *DataInput36 = new int32_t [num_elements_1];
    auto *DataInput37 = new int32_t [num_elements_1];
    auto *DataInput38 = new int32_t [num_elements_1];
    auto *DataInput39 = new int32_t [num_elements_1];

    auto *DataOutput = new int32_t [num_elements_2];

    memset(DataInput0, 0, size_in_bytes_0);

    memset(DataInput1, 0, size_in_bytes_1);
    memset(DataInput2, 0, size_in_bytes_1);
    memset(DataInput3, 0, size_in_bytes_1);
    memset(DataInput4, 0, size_in_bytes_1);
    memset(DataInput5, 0, size_in_bytes_1);
    memset(DataInput6, 0, size_in_bytes_1);
    memset(DataInput7, 0, size_in_bytes_1);
    memset(DataInput8, 0, size_in_bytes_1);
    memset(DataInput9, 0, size_in_bytes_1);
    memset(DataInput10, 0, size_in_bytes_1);
    memset(DataInput11, 0, size_in_bytes_1);
    memset(DataInput12, 0, size_in_bytes_1);
    memset(DataInput13, 0, size_in_bytes_1);
    memset(DataInput14, 0, size_in_bytes_1);
    memset(DataInput15, 0, size_in_bytes_1);
    memset(DataInput16, 0, size_in_bytes_1);
    memset(DataInput17, 0, size_in_bytes_1);
    memset(DataInput18, 0, size_in_bytes_1);
    memset(DataInput19, 0, size_in_bytes_1);
    memset(DataInput20, 0, size_in_bytes_1);
    memset(DataInput21, 0, size_in_bytes_1);
    memset(DataInput22, 0, size_in_bytes_1);
    memset(DataInput23, 0, size_in_bytes_1);
    memset(DataInput24, 0, size_in_bytes_1);
    memset(DataInput25, 0, size_in_bytes_1);
    memset(DataInput26, 0, size_in_bytes_1);
    memset(DataInput27, 0, size_in_bytes_1);
    memset(DataInput28, 0, size_in_bytes_1);
    memset(DataInput29, 0, size_in_bytes_1);
    memset(DataInput30, 0, size_in_bytes_1);
    memset(DataInput31, 0, size_in_bytes_1);
    memset(DataInput32, 0, size_in_bytes_1);
    memset(DataInput33, 0, size_in_bytes_1);
    memset(DataInput34, 0, size_in_bytes_1);
    memset(DataInput35, 0, size_in_bytes_1);
    memset(DataInput36, 0, size_in_bytes_1);
    memset(DataInput37, 0, size_in_bytes_1);
    memset(DataInput38, 0, size_in_bytes_1);
    memset(DataInput39, 0, size_in_bytes_1);

    memset(DataOutput, 0, size_in_bytes_2);

    int32_t* input_list[N+1] = {&DataInput0[0],&DataInput1[0],&DataInput2[0],&DataInput3[0],&DataInput4[0],&DataInput5[0],&DataInput6[0],&DataInput7[0],&DataInput8[0],&DataInput9[0],&DataInput10[0],&DataInput11[0],&DataInput12[0],&DataInput13[0],&DataInput14[0],&DataInput15[0],&DataInput16[0],&DataInput17[0],&DataInput18[0],&DataInput19[0],&DataInput20[0],&DataInput21[0],&DataInput22[0],&DataInput23[0],&DataInput24[0],&DataInput25[0],&DataInput26[0],&DataInput27[0],&DataInput28[0],&DataInput29[0],&DataInput30[0],&DataInput31[0],&DataInput32[0],&DataInput33[0],&DataInput34[0],&DataInput35[0],&DataInput36[0],&DataInput37[0],&DataInput38[0],&DataInput39[0]};

    // Read query: input_0.seq -> DataInput0
    {
        std::ifstream file("../../aie/data/input_0.seq");
        if (!file) { std::cerr << "Error opening input_0.seq" << std::endl; return 1; }
        int32_t number; int j = 0;
        while (file >> number) DataInput0[j++] = number;
    }
    // Read per-lane references: input_1.seq..input_39.seq -> DataInput1..DataInput39
    for (int i = 0; i < N; i++)
    {
        char file_str[100];
        sprintf(file_str, "../../aie/data/input_%d.seq", i + 1);
        std::ifstream file(file_str);
        if (!file) { std::cerr << "Error opening " << file_str << std::endl; return 1; }
        int32_t number; int j = 0;
        while (file >> number) input_list[i + 1][j++] = number;
    }

    std::cout << "Before writing" << std::endl;
    start = std::clock();
    in_buff_1.write(DataInput0);
    in_buff_2.write(DataInput1);
    in_buff_3.write(DataInput2);
    in_buff_4.write(DataInput3);
    in_buff_5.write(DataInput4);
    in_buff_6.write(DataInput5);
    in_buff_7.write(DataInput6);
    in_buff_8.write(DataInput7);
    in_buff_9.write(DataInput8);
    in_buff_10.write(DataInput9);
    in_buff_11.write(DataInput10);
    in_buff_12.write(DataInput11);
    in_buff_13.write(DataInput12);
    in_buff_14.write(DataInput13);
    in_buff_15.write(DataInput14);
    in_buff_16.write(DataInput15);
    in_buff_17.write(DataInput16);
    in_buff_18.write(DataInput17);
    in_buff_19.write(DataInput18);
    in_buff_20.write(DataInput19);
    in_buff_21.write(DataInput20);
    in_buff_22.write(DataInput21);
    in_buff_23.write(DataInput22);
    in_buff_24.write(DataInput23);
    in_buff_25.write(DataInput24);
    in_buff_26.write(DataInput25);
    in_buff_27.write(DataInput26);
    in_buff_28.write(DataInput27);
    in_buff_29.write(DataInput28);
    in_buff_30.write(DataInput29);
    in_buff_31.write(DataInput30);
    in_buff_32.write(DataInput31);
    in_buff_33.write(DataInput32);
    in_buff_34.write(DataInput33);
    in_buff_35.write(DataInput34);
    in_buff_36.write(DataInput35);
    in_buff_37.write(DataInput36);
    in_buff_38.write(DataInput37);
    in_buff_39.write(DataInput38);
    in_buff_40.write(DataInput39);

    // Synchronize input buffers data to device global memory
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    in_buff_1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_4.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_5.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_6.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_7.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_8.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_9.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_10.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_11.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_12.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_13.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_14.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_15.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_16.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_17.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_18.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_19.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_20.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_21.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_22.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_23.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_24.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_25.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_26.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_27.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_28.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_29.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_30.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_31.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_32.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_33.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_34.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_35.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_36.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_37.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_38.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_39.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_40.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    end = std::clock();
    h2d_duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Host to Device: " << h2d_duration << " milliseconds." << std::endl;

    start = std::clock();
    // Execute the compute units
    std::cout << "Run the kernels" << std::endl;

    auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1,in_buff_2,in_buff_3,in_buff_4,in_buff_5,in_buff_6,in_buff_7,in_buff_8,in_buff_9,in_buff_10,in_buff_11,in_buff_12,in_buff_13,in_buff_14,in_buff_15,in_buff_16,in_buff_17,in_buff_18,in_buff_19,in_buff_20,in_buff_21,in_buff_22,in_buff_23,in_buff_24,in_buff_25,in_buff_26,in_buff_27,in_buff_28,in_buff_29,in_buff_30,in_buff_31,in_buff_32,in_buff_33,in_buff_34,in_buff_35,in_buff_36,in_buff_37,in_buff_38,in_buff_39,in_buff_40, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    run_pl_mm2s_1.wait();
    std::cout << "pl_mm2s_1 completed" << std::endl;
    run_pl_s2mm_1.wait();
    std::cout << "pl_s2mm_1 completed" << std::endl;

    end = std::clock();
    kernel_duration = 1000000000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Kernel Time: " << kernel_duration << " nanoseconds." << std::endl;
    std::cout << "Throughput (GCUPS): " << (READ_LEN*REF_LEN*(NK+1)*N*NREF)/kernel_duration << std::endl;

    start = std::clock();
    // Synchronize the output buffer data from the device
    std::cout << "Synchronize the output buffer data from the device" << std::endl;
    out_buff_1.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

    // Read output buffer data to local buffer
    out_buff_1.read(DataOutput);
    end = std::clock();
    d2h_duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Device to Host: " << d2h_duration << " milliseconds." << std::endl;

    // Load ground truth from output_ref.txt and assert against AIE output
    // output_ref.txt layout: N*TOTAL_REFS lines, grouped by lane
    //   lane 0: scores for refs 0..99  (master 0..9, kernel1 10..19, ..., kernel9 90..99)
    //   lane 1: scores for refs 0..99
    //   ...
    // DataOutput layout: DataOutput[lane * (NK+1)*NREF + r]
    {
        const int SCORES_PER_LANE = (NK + 1) * NREF;
        std::ifstream gt_file("../../aie/data/output_ref.txt");
        if (!gt_file) {
            std::cerr << "Error opening output_ref.txt" << std::endl;
            return 1;
        }
        int mismatches = 0;
        int32_t expected;
        for (int lane = 0; lane < N; lane++) {
            for (int r = 0; r < SCORES_PER_LANE; r++) {
                gt_file >> expected;
                int32_t got = DataOutput[lane * SCORES_PER_LANE + r];
                if (got != expected) {
                    std::cerr << "MISMATCH lane=" << lane << " ref=" << r
                              << " expected=" << expected << " got=" << got << std::endl;
                    mismatches++;
                }
            }
        }
        if (mismatches == 0)
            std::cout << "Test Passed: all " << N * SCORES_PER_LANE
                      << " scores match ground truth." << std::endl;
        else
            std::cout << "Test FAILED: " << mismatches << " mismatches." << std::endl;
    }

    for(int i=0;i<N;i++)
    {
    	free(input_list[i]);
    }
    free(DataOutput);
}
