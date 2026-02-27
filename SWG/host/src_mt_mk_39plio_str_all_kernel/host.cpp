// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT
//#include <graph.cpp>
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
    /*auto pl_mm2s_2 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_2}");
    auto pl_mm2s_3 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_3}");
    auto pl_mm2s_4 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_4}");
    auto pl_mm2s_5 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_5}");
    auto pl_mm2s_6 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_6}");*/
    auto pl_s2mm_1 = xrt::kernel(device, uuid, "pl_s2mm:{pl_s2mm_1}");
    /*auto pl_s2mm_2 = xrt::kernel(device, uuid, "pl_s2mm:{pl_s2mm_2}");
    auto pl_s2mm_3 = xrt::kernel(device, uuid, "pl_s2mm:{pl_s2mm_3}");*/

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
    /*auto out_buff_2 = xrt::bo(device, size_in_bytes_2, pl_s2mm_2.group_id(0));
    auto out_buff_3 = xrt::bo(device, size_in_bytes_2, pl_s2mm_3.group_id(0));*/

    // Generate random data and write data to compute unit buffers
    //unsigned int out_size = 2*num_elements;
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
    /*for (unsigned int i = 0; i < num_elements; i++) {
        DataInput0[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
//        DataInput1[i] = (rand() % (1 << 30)) * ((rand()%2) ? 1 : -1);
    }*/
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

    /*std::ifstream file;
	file.open("../../aie_swg/data/input_0.seq");
    if (!file)
    {
            std::cerr << "Error opening file0!" << std::endl;
            return 1;
    }
    int32_t number;
    int i = 0;
    while(file >> number)
    {
    	std::cout << "number : " <<number<< std::endl;
    	DataInput0[i] = number;
    	i++;
    }// Read as a normal integer


    std::ifstream file1;
    file1.open("../../aie_swg/data/input_1.seq");
    if (!file1)
    {
            std::cerr << "Error opening file1!" << std::endl;
            return 1;
    }
    i = 0;
    while(file1 >> number)
    {
    	DataInput1[i] = number;
    	i++;
    }// Read as a normal integer
    std::cout << "DataInput1[i] : " <<DataInput1[i-1]<< std::endl;

    file.close();
    file1.close();
    file1.open("../../aie_swg/data/input_2.seq");
	if (!file1)
	{
			std::cerr << "Error opening file2!" << std::endl;
			return 1;
	}
	i = 0;
	while(file1 >> number)
	{
		DataInput2[i] = number;
		i++;
	}// Read as a normal integer
	std::cout << "DataInput1[i] : " <<DataInput2[i-1]<< std::endl;
	file1.close();
	file1.open("../../aie_swg/data/input_3.seq");
	if (!file1)
	{
			std::cerr << "Error opening file3!" << std::endl;
			return 1;
	}
	i = 0;
	while(file1 >> number)
	{
		DataInput3[i] = number;
		i++;
	}// Read as a normal integer
	std::cout << "DataInput3[i] : " <<DataInput3[i-1]<< std::endl;
	file1.close();*/

    int32_t* input_list[N+1] = {&DataInput0[0],&DataInput1[0],&DataInput2[0],&DataInput3[0],&DataInput4[0],&DataInput5[0],&DataInput6[0],&DataInput7[0],&DataInput8[0],&DataInput9[0],&DataInput10[0],&DataInput11[0],&DataInput12[0],&DataInput13[0],&DataInput14[0],&DataInput15[0],&DataInput16[0],&DataInput17[0],&DataInput18[0],&DataInput19[0],&DataInput20[0],&DataInput21[0],&DataInput22[0],&DataInput23[0],&DataInput24[0],&DataInput25[0],&DataInput26[0],&DataInput27[0],&DataInput28[0],&DataInput29[0],&DataInput30[0],&DataInput31[0],&DataInput32[0],&DataInput33[0],&DataInput34[0],&DataInput35[0],&DataInput36[0],&DataInput37[0],&DataInput38[0],&DataInput39[0]};

	for (int i=0;i<N;i++)
	{
	    std::ifstream file;
        char file_str[100];
        sprintf(file_str, "../../aie_swg/data/src_mt_mk_3plio_str_all_kernel/input_%d.seq", i);
		file.open(file_str);
	    if (!file)
	    {
	            std::cerr << "Error opening file!" << std::endl;
	            return 1;
	    }
	    int32_t number;
	    int j = 0;
	    while(file >> number)
	    {
	    	//std::cout << "number : " <<number<< std::endl;
	    	input_list[i][j] = number;
	    	j++;
	    }
	    file.close();
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
    /*auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, num_elements_2);
    auto run_pl_s2mm_2 = pl_s2mm_2(out_buff_2, nullptr, num_elements_2);
    auto run_pl_s2mm_3 = pl_s2mm_3(out_buff_3, nullptr, num_elements_2);
    auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1, nullptr, num_elements_0);
    auto run_pl_mm2s_2 = pl_mm2s_2(in_buff_2, nullptr, num_elements_0);
    auto run_pl_mm2s_3 = pl_mm2s_3(in_buff_3, nullptr, num_elements_0);
    auto run_pl_mm2s_4 = pl_mm2s_4(in_buff_4, nullptr, num_elements_1);
    auto run_pl_mm2s_5 = pl_mm2s_5(in_buff_5, nullptr, num_elements_1);
    auto run_pl_mm2s_6 = pl_mm2s_6(in_buff_6, nullptr, num_elements_1);*/
    //auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, nullptr, nullptr);
    //auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1, in_buff_2, in_buff_3, in_buff_4, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    //auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr);
    //auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1, in_buff_2, nullptr, nullptr);
    auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1,in_buff_2,in_buff_3,in_buff_4,in_buff_5,in_buff_6,in_buff_7,in_buff_8,in_buff_9,in_buff_10,in_buff_11,in_buff_12,in_buff_13,in_buff_14,in_buff_15,in_buff_16,in_buff_17,in_buff_18,in_buff_19,in_buff_20,in_buff_21,in_buff_22,in_buff_23,in_buff_24,in_buff_25,in_buff_26,in_buff_27,in_buff_28,in_buff_29,in_buff_30,in_buff_31,in_buff_32,in_buff_33,in_buff_34,in_buff_35,in_buff_36,in_buff_37,in_buff_38,in_buff_39,in_buff_40, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    //nw_graph.init();
    //nw_graph.run(1);
    //nw_graph.end();
    // Wait for kernels to complete
    /*run_pl_mm2s_1.wait();
    std::cout << "pl_mm2s_1 completed" << std::endl;
    run_pl_mm2s_2.wait();
    std::cout << "pl_mm2s_2 completed" << std::endl;
    run_pl_mm2s_3.wait();
    std::cout << "pl_mm2s_3 completed" << std::endl;
    run_pl_mm2s_4.wait();
    std::cout << "pl_mm2s_4 completed" << std::endl;
    run_pl_mm2s_5.wait();
    std::cout << "pl_mm2s_5 completed" << std::endl;
    run_pl_mm2s_6.wait();
    std::cout << "pl_mm2s_6 completed" << std::endl;
    run_pl_s2mm_1.wait();
    std::cout << "pl_s2mm_1 completed" << std::endl;
    run_pl_s2mm_2.wait();
    std::cout << "pl_s2mm_2 completed" << std::endl;
	run_pl_s2mm_3.wait();
	std::cout << "pl_s2mm_3 completed" << std::endl;*/
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
    /*out_buff_2.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_buff_3.sync(XCL_BO_SYNC_BO_FROM_DEVICE);*/

    // Read output buffer data to local buffer
    out_buff_1.read(DataOutput);
    end = std::clock();
    d2h_duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Device to Host: " << d2h_duration << " milliseconds." << std::endl;

    /*for (unsigned int i = 0; i < 2; i++) {
		for (unsigned int j = 0; j < num_elements_2; j++) {
			std::cout<<DataOutput[i*num_elements_2+j]<<",";
		}
		std::cout<<std::endl;
    }*/
    /*for (unsigned int j = 0; j < num_elements_2; j++) {
    	if (j%500 == 0)
    		std::cout<<DataOutput[j]<<","<<std::endl;
	}*/
    std::cout<<"Test Passed"<<std::endl;
    //std::cout.flush();
    for(int i=0;i<N;i++)
    {
    	free(input_list[i]);
    }
    free(DataOutput);
}
