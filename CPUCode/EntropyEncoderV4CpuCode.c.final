#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

/*const uint64_t g_table[] = { 10, 21, 49, 1, 1, 1, 1, 1, 23, 1, 1, 1, 1, 23, 84,
		10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 21, 44, 26, 8, 1, 1, 14, 26,
		26, 1, 92, 43, 90, 21, 2, 2, 6, 18, 18, 44, 22, 50, 22, 66, 6, 21, 56,
		14, 6, 66, 6, 21, 56, 14, 6, 66, 6, 21, 56, 14, 6, 5, 10, 8, 8, 30, 58,
		30, 58, 14, 58, 10, 2, 58, 10, 2, 18, 18, 22, 6, 5, 14, 6, 25, 5, 34,
		2, 53, 25, 2, 56, 50, 38, 84, 18, 18, 22, 6, 5, 14, 6, 25, 5, 34, 2,
		53, 25, 2, 56, 50, 38, 84, 5, 76, 42, 26, 5, 30, 26, 10, 14, 124, 78,
		76, 10, 66, 54, 30, 5, 56, 36, 8, 5, 25, 54, 3, 26, 14, 58, 20, 30, 30,
		1, 14, 51, 10, 10, 1 };*/
const uint64_t g_table[] = {2,29,49,1,1,1,1,1,9,1,1,1,1,9,38,2,1,1,1,1,1,1,1,1,1,1,1,1,21,29,1,1,1,14,18,22,1,1,14,18,18,1,62,37,82,29,21,21,9,5,5,14,6,26,6,42,9,29,70,14,9,42,9,29,70,14,9,42,9,29,70,14,9,29,13,2,22,22,30,50,30,50,14,50,2,21,50,2,21,21,5,5,6,9,13,14,9,41,13,10,21,61,41,21,18,26,22,38,1,1,1,1,1,1,1,1,1,1,1,1,5,5,6,9,13,14,9,41,13,10,21,61,41,21,18,26,22,38,1,1,1,1,1,1,1,1,1,1,1,1,13,46,34,18,13,30,18,2,14,98,78,46,2,42,38,30,13,70,42,22,13,10,38,18,18,14,50,26,30,30,1,14,29,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const int table_size = 202;
uint64_t final_table[202];
const uint64_t g_state[] = {0x3FC69FEul<<32, 0};//{0x69feul<<32,0};
uint64_t final_state[2];
const uint64_t g_smste[] = {0,0};
uint64_t final_smste[2];

int main(void)
{
	//data-832-480 is for langchao
	//FILE* fin = fopen("/home/ljh/workspace/EntropyEncoderV4/data-832-480.txt","r");
	FILE* fin = fopen("/home/ljh/workspace/EntropyEncoderV4/data-64-64-output-sequence.txt","r");
	int n;
	fscanf(fin,"%d",&n);
	uint32_t *x = malloc(n*sizeof(uint32_t));
	uint32_t *s = malloc(n*sizeof(uint32_t));
	uint32_t *y = malloc(n*sizeof(uint32_t));

	uint32_t *output0 = malloc(n*sizeof(uint32_t));
	uint32_t *hasOutput0 = malloc(n*sizeof(uint32_t));
	uint32_t *output1 = malloc(n*sizeof(uint32_t));
	uint32_t *numOutput1 = malloc(n*sizeof(uint32_t));
	uint32_t *output2 = malloc(n*sizeof(uint32_t));
	uint32_t *hasOutput2 = malloc(n*sizeof(uint32_t));
	uint32_t *output3 = malloc(n*sizeof(uint32_t));
	uint32_t *hasOutput3 = malloc(n*sizeof(uint32_t));

	uint32_t *output = malloc(n*sizeof(uint32_t));

	/*uint32_t *ivlLow = malloc(n*sizeof(uint32_t));
	uint32_t *ivlCurrRange = malloc(n*sizeof(uint32_t));
	int32_t *bitsLeft = malloc(n*sizeof(int32_t));*/

	/*uint32_t *ivlLowEx = malloc(n*sizeof(uint32_t));
	uint32_t *ivlCurrRangeEx = malloc(n*sizeof(uint32_t));
	int32_t *bitsLeftEx = malloc(n*sizeof(uint32_t));*/

	uint32_t *temp0 = malloc(sizeof(uint32_t));
	uint32_t *temp1 = malloc(sizeof(uint32_t));

	for (int i=0;i<n;++i){
		//fscanf(fin,"%d%d%d%d%d",&x[i],&s[i],&y[i],temp0,temp1);
		fscanf(fin,"%d",&x[i]);
	}

	/*for (int i=0;i<n;++i){
		fscanf(finTmp,"%d%d%d",&ivlLowEx[i], &ivlCurrRangeEx[i], &bitsLeftEx[i]);
	}*/

	/*fscanf(fin,"%d",&m);
	uint32_t* expectedOutput = malloc(m*sizeof(uint32_t));
	for (int i=0;i<m;++i){
		fscanf(fin,"%d",&expectedOutput[i]);
	}*/

	printf("N = %d. Running on DFE.\n",n);
	max_file_t *maxfile = EntropyEncoderV4_init();
	max_engine_t *engine = max_load(maxfile, "*");
	max_actions_t* act = max_actions_init(maxfile, "default");
	max_set_param_uint64t(act, "N", n);
	max_set_mem_range_uint64t(act, "EntropyEncoderV4Kernel", "contextTable", 0, table_size, g_table);
	max_get_mem_range_uint64t(act, "EntropyEncoderV4Kernel", "contextTable", 0, table_size, final_table);
	max_set_mem_range_uint64t(act, "EntropyEncoderV4Kernel", "stateTable", 0, 2, g_state);
	max_get_mem_range_uint64t(act, "EntropyEncoderV4Kernel", "stateTable", 0, 2, final_state);
	max_queue_input(act, "input", x, n * sizeof(uint32_t));
	max_queue_output(act, "output0", output0, n * sizeof(uint32_t));
	max_queue_output(act, "hasOutput0", hasOutput0, n * sizeof(uint32_t));
	max_queue_output(act, "output1", output1, n * sizeof(uint32_t));
	max_queue_output(act, "numOutput1", numOutput1, n * sizeof(uint32_t));
	max_queue_output(act, "output2", output2, n * sizeof(uint32_t));
	max_queue_output(act, "hasOutput2", hasOutput2, n * sizeof(uint32_t));
	max_queue_output(act, "output3", output3, n * sizeof(uint32_t));
	max_queue_output(act, "hasOutput3", hasOutput3, n * sizeof(uint32_t));
	/*max_queue_output(act, "ivlLow", ivlLow, n * sizeof(uint32_t));
	max_queue_output(act, "ivlCurrRange", ivlCurrRange, n * sizeof(uint32_t));
	max_queue_output(act, "bitsLeft", bitsLeft , n * sizeof(int32_t));*/
	max_run(engine, act);
	max_unload(engine);

	printf("maxEngine finish running...\n");
	int idx=0;
	for(int i=0;i<n;i++){


		if(hasOutput0[i] != 0){
			output[idx++] = output0[i];
		}
		while(numOutput1[i] > 0){
			output[idx++] = output1[i];
			numOutput1[i]--;
		}
		if(hasOutput2[i] != 0){
			output[idx++] = output2[i];
		}
		if(hasOutput3[i] != 0){
			output[idx++] = output3[i];
		}
	}
	printf("output.len=%d Checking...\n", idx);

	/*for(int i = 0; i < n; ++i){
		if ((s0[i] == s[i])&&(y0[i]==y[i])){
			++cnt;
		} else if (i-cnt<5){
			printf("[%04d] (s,y) = (%u,%u) != (%u,%u)\n",i,s0[i],y0[i],s[i],y[i]);
		}
	}
*/


	uint32_t bufferForPreValue[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int bufferIdx = 0;

	uint32_t* outputAfterFilter = malloc(n*sizeof(uint32_t));
	int outputIdx = 0;
	int numOf255=0;
	for(int i = 0; i < idx; ++i){
		if(bufferIdx == 0 || output[i] == 255){
			//do nothing
			if(output[i] == 255){
				numOf255++;
				if(numOf255 == 3){
					printf("i=%d next num=%d and %d\n", i, output[i+1], output[i+2]);
				}
			}else{
				numOf255=0;
			}
		}else{
			for(int j=0;j<bufferIdx;j++){
				//printf("%d:%d\n", i, temp);
				//fwrite(&temp,1, 1, fout);
				if(output[i] == 0){
					output[i] = 256;
				}
				//outputAfterFilter[outputIdx++] = (output[i]/256 + bufferForPreValue[j])%256;
				outputAfterFilter[outputIdx++] = (bufferForPreValue[j])%256;

			}
			bufferIdx = 0;
		}
		bufferForPreValue[bufferIdx] = output[i];
		bufferIdx++;
	}
	for(int j=0;j<bufferIdx;j++){
		outputAfterFilter[outputIdx++] = (bufferForPreValue[j])%256;
	}


	printf("outputIdx=%d Checking...\n", outputIdx);
	/*int cnt = 0;
	for(int i = 0; i < m; ++i){
		if(cnt > 5){
			break;
		}else if (outputAfterFilter[i] != expectedOutput[i]){
			printf("[%04d] (outputAfterFilter) = (%u) != (%u)\n",i,outputAfterFilter[i], expectedOutput[i]);
			cnt++;
		}
	}*/
	FILE* fout = fopen("/home/ljh/workspace/EntropyEncoderV4/64-64.bin","wb");
	//256*256
	//const uint64_t headBytes[] ={0 ,0 ,0 ,1 ,64 ,1 ,12 ,1 ,255 ,255 ,1 ,96 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,93 ,240 ,36 ,0 ,0 ,0 ,1 ,66 ,1 ,1 ,1 ,96 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,93 ,160 ,16 ,32 ,32 ,127 ,151 ,211 ,145 ,65 ,237 ,144 ,0 ,0 ,0 ,1 ,68 ,1 ,193 ,144 ,145 ,137 ,164 ,128 ,0 ,0 ,1 ,38 ,1 ,172 ,100};

	const uint64_t headBytes[] = {0 ,0 ,0 ,1 ,64 ,1 ,12 ,1 ,255 ,255 ,1 ,96 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,93 ,240 ,36 ,0 ,0 ,0 ,1 ,66 ,1 ,1 ,1 ,96 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,3 ,0 ,93 ,160 ,32 ,129 ,7 ,249 ,124 ,146 ,84 ,30 ,217 ,0 ,0 ,0 ,1 ,68 ,1 ,193 ,144 ,145 ,137 ,164 ,128 ,0 ,0 ,1 ,38 ,1 ,172 ,100};
	int headerLen = 0x50;
	const uint64_t endBytes[] = {99, 252};
	int endLen = 2;

	uint8_t temp;

	int withHeadAndTrail = 1;

	if(withHeadAndTrail == 1){
		for(int i=0;i<headerLen;i++){
			temp = headBytes[i];
			fwrite(&temp,1, 1, fout);
		}
	}

	int num00 = 0;

	for(int i=0;i<outputIdx;i++){
		fwrite(&outputAfterFilter[i],1, 1, fout);
		if(outputAfterFilter[i] == 0){
			num00++;
		}else{
			num00 = 0;
		}
		if(num00 == 2 && outputAfterFilter[i+1] <= 3){
			temp = 3;
			fwrite(&temp,1, 1, fout);
			num00 = 0;
		}
	}


	/*if(withHeadAndTrail == 1){
		for(int i=0;i<endLen;i++){
			temp = endBytes[i];
			fwrite(&temp,1, 1, fout);
		}
	}*/


	/*for(int i=0;i<m;i++){
		printf("%d\n", output[i]);
	}*/

	//printf("Checked : %d / %d\n",cnt,n);



	//64-64-1
	/*const uint64_t headBytes[] ={0,0,0,1,64,1,12,1,255,255,1,96,0,0,3,0,0,3,0,0,3,0,0,3,0,93,240,36,0,0,0,1,66,1,1,1,96,0,0,3,0,0,3,0,0,3,0,0,3,0,93,160,32,129,7,249,124,146,84,30,217,0,0,0,1,68,1,193,144,145,137,164,128,0,0,1,38,1,172,100};

	//176-144-1
	//const uint64_t headBytes[] ={0,0,0,1,64,1,12,1,255,255,1,96,0,0,3,0,0,3,0,0,3,0,0,3,0,93,240,36,0,0,0,1,66,1,1,1,96,0,0,3,0,0,3,0,0,3,0,0,3,0,93,160,22,32,36,127,151,211,145,65,237,144,0,0,0,1,68,1,193,144,145,137,164,128,0,0,1,38,1,172,100};
	const uint64_t endBytes[] = {48};
	FILE* fout = fopen("/home/ljh/workspace/EntropyEncoderV4/64-64.bin","wb");

	uint8_t temp;

	int withHeadAndTrail = 0;

	if(withHeadAndTrail == 1){
		for(int i=0;i<0x50;i++){
			temp = headBytes[i];
			fwrite(&temp,1, 1, fout);
		}
	}



	uint32_t bufferForPreValue[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int bufferIdx = 0;

	for(int i = 0; i < n-1; ++i){
		if(s0[i] == 1 && y0[i] == y[i]){
			if(bufferIdx == 0 || y0[i] == 255){
				//do nothing
			}else{
				for(int j=0;j<bufferIdx;j++){
					temp = (y0[i]/256 + bufferForPreValue[j])%256;
					//printf("%d:%d\n", i, temp);
					fwrite(&temp,1, 1, fout);
				}
				bufferIdx = 0;
			}
			bufferForPreValue[bufferIdx] = y0[i];
			bufferIdx++;
		}
	}

	if(withHeadAndTrail == 1){
		for(int i=0;i<1;i++){
			temp = endBytes[i];
			fwrite(&temp,1, 1, fout);
		}
	}*/


	fclose(fin);
	fclose(fout);
	free(x);
	free(y);
	free(s);
	free(output0);
	free(hasOutput0);
	free(output1);
	free(numOutput1);
	free(output2);
	free(hasOutput2);
	free(output3);
	free(hasOutput3);




	printf("Done.\n");
	return 0;
}
