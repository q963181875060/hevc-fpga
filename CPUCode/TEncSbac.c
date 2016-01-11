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
const uint64_t g_state[] = {0x1000020, 0};//{0x69feul<<32,0};
uint64_t final_state[2];
const uint64_t g_smste[] = {0,0};
uint64_t final_smste[2];

int main(void)
{

	int n = 16;
	int32_t input[] = {-25, -29,-25,-33,-29,-25,-35,-33,-29,-26,-35,-33,-29,-35,-33,-35};
	int32_t *output = malloc(n*sizeof(int32_t));


	printf("N = %d. Running on DFE.\n",n);
	max_file_t *maxfile = TEncSbac_init();
	max_engine_t *engine = max_load(maxfile, "*");
	max_actions_t* act = max_actions_init(maxfile, "default");
	max_set_param_uint64t(act, "N", n);
	max_set_mem_range_uint64t(act, "TEncSbacKernel", "loopVaraiblesTable", 0, 2, g_state);
	max_get_mem_range_uint64t(act, "TEncSbacKernel", "loopVaraiblesTable", 0, 2, final_state);
	max_queue_input(act, "input", input, n * sizeof(int32_t));
	max_queue_output(act, "output", output, n * sizeof(int32_t));

	max_run(engine, act);
	max_unload(engine);

	printf("maxEngine finish running...\n");
	int idx=0;
	for(int i=0;i<n;i++){
		if(output[i] != input[i]+i+1){
			printf("diff at %d, STD=%d, output=%d\n", i, input[i]+i+1, output[i]);
		}
	}
	printf("output.len=%d Checking...\n", idx);



	//free(input);
	free(output);


	printf("Done.\n");
	return 0;
}
