// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <adf.h>
#include "aie_api/aie.hpp"
#include <aie_api/aie_adf.hpp>
#include <aie_api/utils.hpp>
#include <aie_api/operators.hpp>

using namespace aie;
using namespace aie::operators;

#define DATATYPE16 int16
#define DATATYPE32 int32
#define VLEN8 16
#define VLEN4 4

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define REF_LEN 128 // length of reference sequence
#define READ_LEN 128 // length of query sequence
#define AA_LEN 4 // Unique amino acids (A,T,G,C)
#define SEG_LEN int((READ_LEN + VLEN8 - 1)/VLEN8) // Number of elements in each segment for query profile OR Number of vectors
#define NREF 10 // number of references used by each kernel
#define PACKETLEN MIN(REF_LEN,16) // number of amino acids captured in int32 for encoding
#define NPACKET REF_LEN/PACKETLEN // number of int32 numbers required to encode each reference sequence
#define NK 9 // number of kernels excluding master, max 9 for plio 39

const int match = 2, mismatch = 2, gap_open = 3, gap_extension = 1;

/*void print_arr_k(vector<DATATYPE16, VLEN8>* var, int32_t segLen) {
	for (int j = 0; j < segLen; j++, var++)
	{
		print(*var, false);
		printf(" , ");
	}
}*/

void qP_word_aie_k(const int8_t* __restrict read_num,
                     const int8_t* __restrict mat,
                     const int32_t readLen,
                     const int32_t n,
					 vector<DATATYPE16, VLEN8>* __restrict vProfile) {

    //int32_t segLen = (readLen + VLEN8 - 1) / VLEN8;  // Each v8int16 holds 8 int16_t values

    for (int32_t nt = 0; nt < n; ++nt) {
        for (int32_t i = 0; i < SEG_LEN; ++i) {
        	vector<DATATYPE16, VLEN8> vals = zeros<DATATYPE16, VLEN8>();;
            int j = i;
			#pragma unroll
            for (int32_t segNum = 0; segNum < VLEN8; ++segNum) {
                vals[segNum] = (j >= readLen) ? 0 : mat[nt * n + read_num[j]];
                j += SEG_LEN;
            }
            vProfile[nt * SEG_LEN + i] = vals;
        }
    }

}


int32_t sw_aie_word_k(const int8_t* __restrict ref,
							 int32_t refLen,
							 int32_t readLen,
							 const uint8_t weight_gapO, /* will be used as - */
							 const uint8_t weight_gapE, /* will be used as - */
							 const vector<DATATYPE16, VLEN8>* __restrict vProfile,
							 uint16_t terminate) {

	#define saturating_add(a, b) min(max(vector<DATATYPE16, VLEN8>(a + b), broadcast<DATATYPE16, VLEN8>(-32768)), broadcast<DATATYPE16, VLEN8>(32767))
	#define saturating_subu(a, b) max(vector<DATATYPE16, VLEN8>(a - b), zeros<DATATYPE16, VLEN8>())
	#define gtcmp16(a, b) select(zeros<DATATYPE16, VLEN8>(), broadcast<DATATYPE16, VLEN8>(-1), gt(a, b))
	#define max8(m, vm) (m) = reduce_max(vm)

	int32_t maximum = 0;		                     /* the max alignment score */
	int32_t end_read = readLen - 1;
	//int32_t segLen = (readLen + VLEN8 - 1) / VLEN8; /* number of segment */

	/* array to record the largest score of each reference position */
	int16 maxColumn[REF_LEN] = {0};

	/* Define 16 byte 0 vector. */
	vector<DATATYPE16, VLEN8> vZero = zeros<DATATYPE16, VLEN8>();

	/*vector<DATATYPE16, VLEN8> pvHStore[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvHLoad[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvE[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvHmax[SEG_LEN];*/

	vector<DATATYPE16, VLEN8> pvHStoreA[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvHLoadA[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvEA[SEG_LEN];
	vector<DATATYPE16, VLEN8> pvHmaxA[SEG_LEN];

	for (int i=0;i<SEG_LEN;i++)
	{
		pvHStoreA[i] = zeros<DATATYPE16, VLEN8>();
		pvHLoadA[i] = zeros<DATATYPE16, VLEN8>();
		pvEA[i] = zeros<DATATYPE16, VLEN8>();
		pvHmaxA[i] = zeros<DATATYPE16, VLEN8>();
	}

	vector<DATATYPE16, VLEN8>* pvHStore = &pvHStoreA[0];
	vector<DATATYPE16, VLEN8>* pvHLoad = &pvHLoadA[0];
	vector<DATATYPE16, VLEN8>* pvE = &pvEA[0];
	vector<DATATYPE16, VLEN8>* pvHmax = &pvHmaxA[0];

	int32_t i, j, k;
	/* 16 byte insertion begin vector */
	//__m128i vGapO = _mm_set1_epi16(weight_gapO);
	vector<DATATYPE16, VLEN8> vGapO = broadcast<DATATYPE16, VLEN8>(weight_gapO);

	/* 16 byte insertion extension vector */
	//__m128i vGapE = _mm_set1_epi16(weight_gapE);
	vector<DATATYPE16, VLEN8> vGapE = broadcast<DATATYPE16, VLEN8>(weight_gapE);

	//__m128i vMaxScore = vZero; /* Trace the highest score of the whole SW matrix. */
	//__m128i vMaxMark = vZero; /* Trace the highest score till the previous column. */
	//__m128i vTemp;
	vector<DATATYPE16, VLEN8> vMaxScore = vZero;
	vector<DATATYPE16, VLEN8> vMaxMark = vZero;
	vector<DATATYPE16, VLEN8> vTemp;

	int32_t edge, begin = 0, end = refLen, step = 1;

	for (i = begin; i != end; i += step) {
		//int32_t cmp;
		vector<DATATYPE16, VLEN8> e, vF = vZero; /* Initialize F value to 0. Any errors to vH values will be corrected in the Lazy_F loop.*/
		vector<DATATYPE16, VLEN8> vH = pvHStore[SEG_LEN - 1];
		//printf("\nvH before upshift:");
		//print(vH, false);
		// Concatenate the tail and a zero at the end
		vH.push(0);
		//printf("\nvH after upshift:");
		//print(vH, false);

		/* Swap the 2 H buffers. */
		vector<DATATYPE16, VLEN8>* pv = pvHLoad;

		vector<DATATYPE16, VLEN8> vMaxColumn = vZero; /* vMaxColumn is used to record the max values of column i. */

		const vector<DATATYPE16, VLEN8>* vP = vProfile + ref[i] * SEG_LEN; /* Right part of the vProfile */
		//printf("\nvP:");
		//print(*vP, false);
		pvHLoad = pvHStore;
		pvHStore = pv;

		//printf("\npvHLoad:");
		//print_arr(pvHLoad, SEG_LEN);
		//printf("\npvHStore:");
		//print_arr(pvHStore, SEG_LEN);

		/* inner loop to process the query sequence */
		for (j = 0; j < SEG_LEN; j ++) {
			/*printf("\nvH before saturating_add:");
			print(vH, false);
			printf("\nvP[j] before saturating_add:");
			print(vP[j], false);*/
			vH = saturating_add(vH, vP[j]);
			//printf("\nvH after saturating_add:");
			//print(vH, false);

			/* Get max from vH, vE and vF. */
			e = pvE[j];
			//printf("\ne after load:");
			//print(e, false);
			vH = max(vH, e);
			//printf("\nvH after max(vH, e):");
			//print(vH, false);
			vH = max(vH, vF);
			//printf("\nvH after max(vH, vF):");
			//print(vH, false);
			vMaxColumn = max(vMaxColumn, vH);

			/* Save vH values. */
			pvHStore[j] = vH;
			//printf("\npvHStore after saving vH values :");
			//print_arr(pvHStore, SEG_LEN);

			/* Update vE value. */
			vH = saturating_subu(vH, vGapO); /* saturation arithmetic, result >= 0 */
			//printf("\nvH after saturating_subu:");
			//print(vH, false);
			e = saturating_subu(e, vGapE);
			e = max(e, vH);
			pvE[j] = e;

			/* Update vF value. */
			//printf("\nvF before saturating_subu:");
			//print(vF, false);
			vF = saturating_subu(vF, vGapE);
			vF = max(vF, vH);

			/* Load the next vH. */
			vH = pvHLoad[j];

			/*printf("\nvH:");
			print(vH, false);
			printf(" vF:");
			print(vF, false);*/
		}

		/* Lazy_F loop: has been revised to disallow adjecent insertion and then deletion, so don't update E(i, j), learn from SWPS3 */
		for (k = 0; k < VLEN8; ++k) {
			vF.push(0);
			for (j = 0; j < SEG_LEN; ++j) {
				vH = pvHStore[j];
				vH = max(vH, vF);
				vMaxColumn = max(vMaxColumn, vH); //newly added line
				pvHStore[j] = vH;
				//printf("\npvHStore in lazy_F loop :");
				//print_arr(pvHStore, SEG_LEN);
				vH = saturating_subu(vH, vGapO);
				vF = saturating_subu(vF, vGapE);
				/*printf("\nvH in lazy_F loop :");
				print(vH, false);
				printf(" vF in lazy_F loop :");
				print(vF, false);*/
				if (equal(gtcmp16(vF, vH), zeros<DATATYPE16, VLEN8>())) goto end;
			}
		}

end:
		vMaxScore = max(vMaxScore, vMaxColumn);
		//vTemp = eq(vMaxMark, vMaxScore);
		//cmp = reduce_or(vTemp);
		//printf("%B\n", equal(vMaxMark, vMaxScore));
		//printf("%d\n", equal(vMaxMark, vMaxScore));
		//printf("%B\n", !equal(vMaxMark, vMaxScore));
		//printf("%d\n", !equal(vMaxMark, vMaxScore));
		/*printf("\ni: %d\n",i);
		printf("vMaxScore:");
		print(vMaxScore, false);
		printf(" vMaxColumn:");
		print(vMaxColumn, false);
		printf(" vMaxMark:");
		print(vMaxMark, false);*/
		if (!equal(vMaxMark, vMaxScore)) {
			uint16_t temp;
			vMaxMark = vMaxScore;
			max8(temp, vMaxScore);
			vMaxScore = vMaxMark;

			if (temp > maximum) {
				maximum = temp;
				//end_ref = i;
				for (j = 0; j < SEG_LEN; ++j) pvHmax[j] = pvHStore[j];
			}
		}

		/* Record the max score of current column. */
		max8(maxColumn[i], vMaxColumn);
		if (maxColumn[i] == terminate) break;
		//if (i == 1) break;
	}

	return maximum;
}


void aie_swg_str_kernel(input_stream_int32* __restrict in0, input_stream_int32* __restrict in1, output_stream_int32* __restrict out)
{
	/*static unsigned long long cycle_num[2];
	tile tile=tile::current();
	volatile unsigned long long *p_cycle=cycle_num;
	*p_cycle=tile.cycles();*/
	//printf("Running on tile col=%d, row=%d, ", __XCHESS_TILE__C, __XCHESS_TILE__R);
	//printf("start cycles=%lld, ",cycle_num[0]);

	int8_t ref[REF_LEN], read[READ_LEN];
	int8_t mat[AA_LEN*AA_LEN], l, k;
	int32_t ref_enc[NREF*NPACKET];
	int32_t kernel_num = readincr(in0);
	if (kernel_num<NK) writeincr(out,(kernel_num+1));

	for (unsigned int i=0; i<NREF*NPACKET; i++)
		chess_prepare_for_pipelining
	{
		ref_enc[i] = readincr(in0);
	}
	//printf("after ref_enc, %d %d, ", ref_enc[0], ref_enc[1]);
	for (unsigned int i=0; i<(NK-kernel_num)*NREF*NPACKET; i++)
		chess_prepare_for_pipelining
	{
		writeincr(out,readincr(in0));// pass remaining refs
	}
	//printf("after pass remaining refs, kernel_num : %d, ", kernel_num);
	for (unsigned int i=0; i<NPACKET; i++)
		chess_prepare_for_pipelining
	{
		int32_t data = readincr(in1);// read query data
		for (int j=PACKETLEN-1; j>=0; j--)
			chess_prepare_for_pipelining
		{
			read[i*PACKETLEN-j+PACKETLEN-1] = (data >> (j * 2)) & 0x3;
		}
	}
	//printf("***after read query data, %d %d %d %d, ", read[0], read[1], read[READ_LEN-2], read[READ_LEN-1]);
	for (l = k = 0; l < AA_LEN; ++l)
	{
		for (int m = 0; m < AA_LEN; ++m)
			mat[k++] = l == m ? match : - mismatch;	/* weight_match : -weight_mismatch */
	}
	vector<DATATYPE16, VLEN8> vProfile[AA_LEN*SEG_LEN];//size must be n*segLen
	aie::vector<DATATYPE16, VLEN8>* profile_word;
	qP_word_aie_k(&read[0], &mat[0], READ_LEN, AA_LEN, &vProfile[0]);
	//print_arr(vProfile, AA_LEN*SEG_LEN);
	profile_word = &vProfile[0];
	//printf("after profile_word, ");
	//print_arr_k(vProfile, AA_LEN*SEG_LEN);
	int32_t max_arr[NREF];
	for (unsigned int k=0; k<NREF; k++)
		chess_prepare_for_pipelining
	{

		for (unsigned int i=0; i<NPACKET; i++)
			chess_prepare_for_pipelining
		{
			int32_t data = ref_enc[k*NPACKET+i];
			for (int j=PACKETLEN-1; j>=0; j--)
				chess_prepare_for_pipelining
			{
				ref[i*PACKETLEN-j+PACKETLEN-1] = (data >> (j * 2)) & 0x3;
			}
		}

		max_arr[k] = sw_aie_word_k(&ref[0], REF_LEN, READ_LEN, gap_open, gap_extension, profile_word, -1);
		//writeincr(out, maximum);
		//printf("maximum : %d, ", maximum);
		//if (kernel_num==NK) writeincr(out, maximum);
	}
	for (int i=0; i<kernel_num*NREF; i++)
		chess_prepare_for_pipelining
	{
		writeincr(out, readincr(in0));
	}
	for (int i=0; i<NREF; i++)
		chess_prepare_for_pipelining
	{
		writeincr(out, max_arr[i]);
	}
	//*(p_cycle+1)=tile.cycles();//cycle_num[1]
	//printf("cycles=%lld\n",cycle_num[1]-cycle_num[0]);
}

