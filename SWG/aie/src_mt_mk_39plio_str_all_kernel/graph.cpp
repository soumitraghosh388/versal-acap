// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <graph.hpp>
#include <iostream>
#include <fstream>

simpleGraph swg_graph;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {
    swg_graph.init();
    swg_graph.run(1);
    swg_graph.end();
    return 0;
}
#endif
