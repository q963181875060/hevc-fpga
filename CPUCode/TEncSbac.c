#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"



uint64_t g_state[] = {0x1000020, 0};
uint64_t final_state[2] = {0,0};

uint64_t coded_sub_block_flag_buffer[] = {0, 0};
uint64_t coded_sub_block_flag_final_buffer[] = {0, 0};

uint64_t *sig_coeff_flag_buffer;
uint64_t *sig_coeff_flag_final_buffer;

uint64_t *coeff_abs_level_greater1_flag_buffer;
uint64_t *coeff_abs_level_greater1_flag_final_buffer;

uint64_t *coeff_abs_level_greater2_flag_buffer;
uint64_t *coeff_abs_level_greater2_flag_final_buffer;

uint64_t *coeff_sign_flag_buffer;
uint64_t *coeff_sign_flag_final_buffer;

uint64_t *coeff_abs_level_remaining_buffer;
uint64_t *coeff_abs_level_remaining_final_buffer;

const uint64_t scan_32[] ={0,32,1,64,33,2,96,65,34,3,97,66,35,98,67,99,128,160,129,192,161,130,224,193,162,131,225,194,163,226,195,227,4,36,5,68,37,6,100,69,38,7,101,70,39,102,71,103,256,288,257,320,289,258,352,321,290,259,353,322,291,354,323,355,132,164,133,196,165,134,228,197,166,135,229,198,167,230,199,231,8,40,9,72,41,10,104,73,42,11,105,74,43,106,75,107,384,416,385,448,417,386,480,449,418,387,481,450,419,482,451,483,260,292,261,324,293,262,356,325,294,263,357,326,295,358,327,359,136,168,137,200,169,138,232,201,170,139,233,202,171,234,203,235,12,44,13,76,45,14,108,77,46,15,109,78,47,110,79,111,512,544,513,576,545,514,608,577,546,515,609,578,547,610,579,611,388,420,389,452,421,390,484,453,422,391,485,454,423,486,455,487,264,296,265,328,297,266,360,329,298,267,361,330,299,362,331,363,140,172,141,204,173,142,236,205,174,143,237,206,175,238,207,239,16,48,17,80,49,18,112,81,50,19,113,82,51,114,83,115,640,672,641,704,673,642,736,705,674,643,737,706,675,738,707,739,516,548,517,580,549,518,612,581,550,519,613,582,551,614,583,615,392,424,393,456,425,394,488,457,426,395,489,458,427,490,459,491,268,300,269,332,301,270,364,333,302,271,365,334,303,366,335,367,144,176,145,208,177,146,240,209,178,147,241,210,179,242,211,243,20,52,21,84,53,22,116,85,54,23,117,86,55,118,87,119,768,800,769,832,801,770,864,833,802,771,865,834,803,866,835,867,644,676,645,708,677,646,740,709,678,647,741,710,679,742,711,743,520,552,521,584,553,522,616,585,554,523,617,586,555,618,587,619,396,428,397,460,429,398,492,461,430,399,493,462,431,494,463,495,272,304,273,336,305,274,368,337,306,275,369,338,307,370,339,371,148,180,149,212,181,150,244,213,182,151,245,214,183,246,215,247,24,56,25,88,57,26,120,89,58,27,121,90,59,122,91,123,896,928,897,960,929,898,992,961,930,899,993,962,931,994,963,995,772,804,773,836,805,774,868,837,806,775,869,838,807,870,839,871,648,680,649,712,681,650,744,713,682,651,745,714,683,746,715,747,524,556,525,588,557,526,620,589,558,527,621,590,559,622,591,623,400,432,401,464,433,402,496,465,434,403,497,466,435,498,467,499,276,308,277,340,309,278,372,341,310,279,373,342,311,374,343,375,152,184,153,216,185,154,248,217,186,155,249,218,187,250,219,251,28,60,29,92,61,30,124,93,62,31,125,94,63,126,95,127,900,932,901,964,933,902,996,965,934,903,997,966,935,998,967,999,776,808,777,840,809,778,872,841,810,779,873,842,811,874,843,875,652,684,653,716,685,654,748,717,686,655,749,718,687,750,719,751,528,560,529,592,561,530,624,593,562,531,625,594,563,626,595,627,404,436,405,468,437,406,500,469,438,407,501,470,439,502,471,503,280,312,281,344,313,282,376,345,314,283,377,346,315,378,347,379,156,188,157,220,189,158,252,221,190,159,253,222,191,254,223,255,904,936,905,968,937,906,1000,969,938,907,1001,970,939,1002,971,1003,780,812,781,844,813,782,876,845,814,783,877,846,815,878,847,879,656,688,657,720,689,658,752,721,690,659,753,722,691,754,723,755,532,564,533,596,565,534,628,597,566,535,629,598,567,630,599,631,408,440,409,472,441,410,504,473,442,411,505,474,443,506,475,507,284,316,285,348,317,286,380,349,318,287,381,350,319,382,351,383,908,940,909,972,941,910,1004,973,942,911,1005,974,943,1006,975,1007,784,816,785,848,817,786,880,849,818,787,881,850,819,882,851,883,660,692,661,724,693,662,756,725,694,663,757,726,695,758,727,759,536,568,537,600,569,538,632,601,570,539,633,602,571,634,603,635,412,444,413,476,445,414,508,477,446,415,509,478,447,510,479,511,912,944,913,976,945,914,1008,977,946,915,1009,978,947,1010,979,1011,788,820,789,852,821,790,884,853,822,791,885,854,823,886,855,887,664,696,665,728,697,666,760,729,698,667,761,730,699,762,731,763,540,572,541,604,573,542,636,605,574,543,637,606,575,638,607,639,916,948,917,980,949,918,1012,981,950,919,1013,982,951,1014,983,1015,792,824,793,856,825,794,888,857,826,795,889,858,827,890,859,891,668,700,669,732,701,670,764,733,702,671,765,734,703,766,735,767,920,952,921,984,953,922,1016,985,954,923,1017,986,955,1018,987,1019,796,828,797,860,829,798,892,861,830,799,893,862,831,894,863,895,924,956,925,988,957,926,1020,989,958,927,1021,990,959,1022,991,1023};
const uint64_t scan_16[] ={0,16,1,32,17,2,48,33,18,3,49,34,19,50,35,51,64,80,65,96,81,66,112,97,82,67,113,98,83,114,99,115,4,20,5,36,21,6,52,37,22,7,53,38,23,54,39,55,128,144,129,160,145,130,176,161,146,131,177,162,147,178,163,179,68,84,69,100,85,70,116,101,86,71,117,102,87,118,103,119,8,24,9,40,25,10,56,41,26,11,57,42,27,58,43,59,192,208,193,224,209,194,240,225,210,195,241,226,211,242,227,243,132,148,133,164,149,134,180,165,150,135,181,166,151,182,167,183,72,88,73,104,89,74,120,105,90,75,121,106,91,122,107,123,12,28,13,44,29,14,60,45,30,15,61,46,31,62,47,63,196,212,197,228,213,198,244,229,214,199,245,230,215,246,231,247,136,152,137,168,153,138,184,169,154,139,185,170,155,186,171,187,76,92,77,108,93,78,124,109,94,79,125,110,95,126,111,127,200,216,201,232,217,202,248,233,218,203,249,234,219,250,235,251,140,156,141,172,157,142,188,173,158,143,189,174,159,190,175,191,204,220,205,236,221,206,252,237,222,207,253,238,223,254,239,255};
const uint64_t notFirstGroupNeighbourhoodContextOffset[]  = {3, 0};
int main(void)
{

	int n = 16;
	int32_t input[] = {-25, -29,-25,-33,-29,-25,-35,-33,-29,-26,-35,-33,-29,-35,-33,-35};
	int32_t *output = malloc(n*sizeof(int32_t));
	uint64_t coded_sub_block_flag_cpu[] = {298};

	sig_coeff_flag_buffer = malloc(n*sizeof(uint64_t));
	sig_coeff_flag_final_buffer = malloc(n*sizeof(uint64_t));
	uint64_t sig_coeff_flag_cpu[] = {326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 327, 327, 327, 327, 327, 328};
	for(int i=0;i<n;i++){
		sig_coeff_flag_buffer[i] = 0;
		sig_coeff_flag_final_buffer[i] = 0;
	}

	coeff_abs_level_greater1_flag_buffer = malloc(8*sizeof(uint64_t));
	coeff_abs_level_greater1_flag_final_buffer = malloc(8*sizeof(uint64_t));
	uint64_t coeff_abs_level_greater1_flag_cpu[] = {415, 414, 414, 414, 414, 414, 414, 414};

	coeff_abs_level_greater2_flag_buffer = malloc(2*sizeof(uint64_t));
	coeff_abs_level_greater2_flag_final_buffer = malloc(2*sizeof(uint64_t));
	uint64_t coeff_abs_level_greater2_flag_cpu[] = {432, 0};

	coeff_sign_flag_buffer = malloc(2*sizeof(uint64_t));
	coeff_sign_flag_final_buffer = malloc(2*sizeof(uint64_t));
	uint64_t coeff_sign_flag_cpu[] = {553647888, 0};

	coeff_abs_level_remaining_buffer = malloc(n*sizeof(uint64_t));
	coeff_abs_level_remaining_final_buffer = malloc(n*sizeof(uint64_t));
	uint64_t coeff_abs_level_remaining_cpu[] = {2306122320063759364,2305981578280437508,2305876016574236419,2305858420093224707,2305845217363757828,2305845217363756804,2305849619705233668,2305845217363758852,2305845217363758084,2305845217363757316,2305849619705233924,2305849619705233412,2305845217363758084,2305849619705233924,2305849619705233412,2305849619705233924};
	for(int i=0;i<n;i++){
		coeff_abs_level_remaining_buffer[i] = 0;
		//coeff_abs_level_remaining_final_buffer[i] = 0;
	}

	printf("N = %d. Running on DFE.\n",n);
	max_file_t *maxfile = TEncSbac_init();
	max_engine_t *engine = max_load(maxfile, "*");
	max_actions_t* act = max_actions_init(maxfile, "default");

	int compId = 0;
	int width = 32;
	int scanFirstPos = 1023;
	int sigRight = 0;
	int sigLower = 0;

	max_set_param_uint64t(act, "N", n);
	max_set_param_uint64t(act, "compId", compId);
	max_set_param_uint64t(act, "width", width);
	max_set_param_uint64t(act, "scanFirstPos", scanFirstPos);
	max_set_param_uint64t(act, "sigRight", sigRight);
	max_set_param_uint64t(act, "sigLower", sigLower);

	max_set_mem_range_uint64t(act, "TEncSbacKernel", "loopVaraiblesTable", 0, 2, g_state);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "loopVaraiblesTable", 0, 2, final_state);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "coded_sub_block_flag_buffer", 0, 2, coded_sub_block_flag_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "coded_sub_block_flag_buffer", 0, 2, coded_sub_block_flag_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "sig_coeff_flag_buffer", 0, n, sig_coeff_flag_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "sig_coeff_flag_buffer", 0, n, sig_coeff_flag_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_greater1_flag_buffer", 0, 8, coeff_abs_level_greater1_flag_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_greater1_flag_buffer", 0, 8, coeff_abs_level_greater1_flag_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_greater2_flag_buffer", 0, 2, coeff_abs_level_greater2_flag_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_greater2_flag_buffer", 0, 2, coeff_abs_level_greater2_flag_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "coeff_sign_flag_buffer", 0, 2, coeff_sign_flag_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "coeff_sign_flag_buffer", 0, 2, coeff_sign_flag_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_remaining_buffer", 0, n, coeff_abs_level_remaining_buffer);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "coeff_abs_level_remaining_buffer", 0, n, coeff_abs_level_remaining_final_buffer);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "scan_32", 0, 1024, scan_32);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "scan_16", 0, 256, scan_16);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "notFirstGroupNeighbourhoodContextOffset", 0, 2, notFirstGroupNeighbourhoodContextOffset);
	max_queue_input(act, "input", input, n * sizeof(int32_t));
	max_queue_output(act, "output", output, n * sizeof(int32_t));

	max_run(engine, act);
	max_unload(engine);

	printf("maxEngine finish running...\n");
	int idx=0;

	printf("Output Checking...\n");
	for(int i=0;i<n;i++){
		if(output[i] != input[i]+i){
			printf("diff at %d, STD=%d, output=%d\n", i, input[i]+i, output[i]);
		}
	}

	printf("coded_sub_block_flag_output Checking...\n");
	if(coded_sub_block_flag_cpu[0] != coded_sub_block_flag_final_buffer[0]){
		printf("diff coded_sub_block_flag, STD=%d, output=%d\n", coded_sub_block_flag_cpu[0], coded_sub_block_flag_final_buffer[0]);
	}

	printf("sig_coeff_flag_output Checking...\n");
	for(int i=0;i<n;i++){
		if(sig_coeff_flag_cpu[i] != sig_coeff_flag_final_buffer[i]){
			printf("diff sig_coeff_flag, STD=%d, output=%d\n", sig_coeff_flag_cpu[i], sig_coeff_flag_final_buffer[i]);
		}
	}

	printf("coeff_abs_level_greater1_flag_output Checking...\n");
	for(int i=0;i<8;i++){
		if(coeff_abs_level_greater1_flag_cpu[i] != coeff_abs_level_greater1_flag_final_buffer[i]){
			printf("diff coeff_abs_level_greater1_flag, STD=%d, output=%d\n", coeff_abs_level_greater1_flag_cpu[i], coeff_abs_level_greater1_flag_final_buffer[i]);
		}
	}

	printf("coeff_abs_level_greater2_flag_output Checking...\n");
	for(int i=0;i<1;i++){
		if(coeff_abs_level_greater2_flag_cpu[i] != coeff_abs_level_greater2_flag_final_buffer[i]){
			printf("diff coeff_abs_level_greater2_flag, STD=%d, output=%d\n", coeff_abs_level_greater2_flag_cpu[i], coeff_abs_level_greater2_flag_final_buffer[i]);
		}
	}

	printf("coeff_sign_flag_flag_output Checking...\n");
	for(int i=0;i<1;i++){
		if(coeff_sign_flag_cpu[i] != coeff_sign_flag_final_buffer[i]){
			printf("diff coeff_abs_level_greater2_flag, STD=%d, output=%d\n", coeff_sign_flag_cpu[i], coeff_sign_flag_final_buffer[i]);
		}
	}

	printf("coeff_abs_level_remaining_output Checking...\n");
	for(int i=0;i<n;i++){
		if(coeff_abs_level_remaining_cpu[i] != coeff_abs_level_remaining_final_buffer[i]){
			printf("diff coeff_abs_level_remaining[%d], STD=%ld, output=%ld\n", i, coeff_abs_level_remaining_cpu[i], coeff_abs_level_remaining_final_buffer[i]);
		}
	}
	//free(input);
	free(output);
	free(sig_coeff_flag_buffer);
	free(sig_coeff_flag_final_buffer);
	free(coeff_abs_level_greater1_flag_buffer);
	free(coeff_abs_level_greater1_flag_final_buffer);
	free(coeff_abs_level_greater2_flag_buffer);
	free(coeff_abs_level_greater2_flag_final_buffer);
	free(coeff_sign_flag_buffer);
	free(coeff_sign_flag_final_buffer);
	free(coeff_abs_level_remaining_buffer);
	free(coeff_abs_level_remaining_final_buffer);
	printf("Done.\n");
	return 0;
}
