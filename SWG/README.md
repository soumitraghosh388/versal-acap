## Setup Steps :

## 1. Compile AIE graph
       aiecompiler -v -Xchess=main:darts.xargs=-nb -include="/home/Xilinx/Vitis/2022.2/aietools/include" -include="/home/Xilinx/Vitis_HLS/2022.2/include" -include="../" -include="../src" -include="../data" -target=hw   -platform=/opt/xilinx/platforms/xilinx_vck5000_gen4x8_qdma_2_202220_1/xilinx_vck5000_gen4x8_qdma_2_202220_1.xpfm -workdir=./Work /root/workspace/aie_swg/src/graph.cpp 

## 2. Compile PL kernels
       /home/Xilinx/Vitis/2022.2/bin/v++ --target hw --compile -I"../src" -o"build/pl_s2mm.xo" "../src/pl_s2mm.cpp"
/home/Xilinx/Vitis/2022.2/bin/v++ --target hw --compile -I"../src" -o"build/pl_mm2s.xo" "../src/pl_mm2s.cpp"

## 3. Create xsa file
       /home/Xilinx/Vitis/2022.2/bin/v++ --target hw --link --config ../config.cfg -o"binary_container_1.xsa" ../../datamovers_swg_pl/Hardware/build/pl_mm2s.xo ../../datamovers_swg_pl/Hardware/build/pl_s2mm.xo ../../aie_swg/Hardware/libadf.a -f xilinx_vck5000_gen4x8_qdma_2_202220_1

## 4. Create xclbin file
       /home/Xilinx/Vitis/2022.2/bin/v++ --package -t hw --platform xilinx_vck5000_gen4x8_qdma_2_202220_1 --save-temps \
         ../../aie_swg_system_hw_link/Hardware/binary_container_1.xsa \
         ../../aie_swg/Hardware/libadf.a \
         --temp_dir _x_temp \
         --report_dir reports/ \
         --package.boot_mode=ospi \
         -o binary_container_1.xclbin

## 5. Compile host source code
       g++ -std=c++1y -std=c++17 -DVITIS_PLATFORM=xilinx_vck5000_gen4x8_qdma_2_202220_1 -D__USE_XOPEN2K8 -I/opt/xilinx/xrt/include/ -I/home/Xilinx/Vitis_HLS/2022.2/include/ -O2 -g -Wall -c -fmessage-length=0 -o "src/host.o" "../src/host.cpp"

## 6. Create host executable
       g++ -o "host_swg_x86" src/host.o -lxilinxopencl -lxrt_coreutil -lpthread -lrt -lstdc++ -L/opt/xilinx/xrt/lib/ -Wl,-rpath-link,/opt/xilinx/xrt/lib

## 7. Execute in Hardware
       ./host_swg_x86 ../../aie_swg_system/Hardware/binary_container_1.xclbin

#### Note : 
1. change the path as needed, experimented on VCK5000 hardware
2. For Stripped implementaion (SSW), when a gap is opened, the gap open penalty alone is applied.
