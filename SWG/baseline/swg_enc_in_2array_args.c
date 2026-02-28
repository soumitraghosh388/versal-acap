// Copyright Soumitra Ghosh, IIIT Hyderabad, India, 2025
//
// SPDX-License-Identifier: MIT
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_SEQ_LEN 160 // Increased to handle larger command line strings

const int32_t gap_open = -3, gap_extension = -1;
const int match = 2, mismatch = -2;

int16_t max2(int16_t a, int16_t b) {
    return (a < b) ? b : a;
}

int16_t score_match(int8_t base1, int8_t base2) {
    return (base1 == base2) ? match : mismatch;  
}

int main(int argc, char *argv[]) {
    // 1. Check for command line arguments
    if (argc < 3) {
        printf("Usage: %s <query_sequence> <reference_sequence>\n", argv[0]);
        printf("Example: %s 331100 331122\n", argv[0]);
        return -1;
    }

    // 2. Extract sequences from arguments
    char *q_str = argv[1];
    char *r_str = argv[2];
    int qlen = strlen(q_str);
    int rlen = strlen(r_str);

    if (qlen >= MAX_SEQ_LEN || rlen >= MAX_SEQ_LEN) {
        printf("Error: Sequence exceeds MAX_SEQ_LEN (%d)\n", MAX_SEQ_LEN);
        return -1;
    }

    // 3. Convert character strings to int8_t arrays (0,1,2,3)
    int8_t query_num[MAX_SEQ_LEN];
    int8_t ref_num[MAX_SEQ_LEN];

    for (int i = 0; i < qlen; i++) query_num[i] = q_str[i] - '0';
    for (int i = 0; i < rlen; i++) ref_num[i] = r_str[i] - '0';

    // 4. Initialize DP buffers
    int16_t nogap[MAX_SEQ_LEN] = {0};
    int16_t b_gap[MAX_SEQ_LEN] = {gap_open};

    int16_t score = 0;
    int16_t last_nogap, prev_nogap;

    // 5. SWG Alignment Loop
    for (int i = 0; i < qlen; ++i) {
        int16_t a_gap = gap_open;
        last_nogap = 0;
        prev_nogap = 0;

        for (int j = 0; j < rlen; ++j) {
            // Horizontal gap (a_gap)
            a_gap = max2((last_nogap + gap_open), (a_gap + gap_extension));

            // Vertical gap (b_gap)
            b_gap[j] = max2((nogap[j] + gap_open), (b_gap[j] + gap_extension));
            last_nogap = max2((prev_nogap + score_match(query_num[i], ref_num[j])) , 0 ) ;
            last_nogap = max2(last_nogap, a_gap);
            last_nogap = max2(last_nogap, b_gap[j]);

            prev_nogap = nogap[j];
            nogap[j] = last_nogap;
            score = max2(score, last_nogap);
        }
    }

    printf("Best alignment score: %d\n", score);

    return score;
}
