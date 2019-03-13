/* Caleb Obeng
	I pledge my honor that I have abided by the stevens honor system. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv){
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command-line arguments\n usage: %s <width of matrix> <width of block>\n", argv[0]);
		return -1;
	}

	int matrix_size = atoi(argv[1]);
	int block_size = atoi(argv[2]);
	if(matrix_size < block_size){
		fprintf(stderr, "block cannot be bigger than the matrix\n");
		return -1;
	}

	float *A = (float *) malloc(matrix_size*matrix_size*sizeof(float));
	float *AT = (float *) malloc(matrix_size*matrix_size*sizeof(float));
	srand(time(NULL));
/*
	printf("input matrix\n");
	for(int i=0; i<matrix_size*matrix_size; i++){
		if((i!=0) && (i%matrix_size == 0)){
			printf("\n");
		}
		float x = (float)( (rand()) / (float)RAND_MAX);
		float y = (x * ( 100 + 100 ));
		printf("%f ", y);
		A[i] = y;
	}
	printf("\n\n");
*/
	//start transpose
	struct timeval start, end;
	gettimeofday(&start, NULL);
	printf("Start Time: %ld\n", (start.tv_sec * 1000000 + start.tv_usec));
	for(int i=0; i<matrix_size;i+=block_size){
		for(int j=0; j<matrix_size; j+=block_size){
			for(int k=i; k<i + block_size; k++){
				for(int l = j; l < j + block_size; l++){
					AT[k + l*matrix_size] = A[k*matrix_size + l];
				}
			}
		}
	}
	//end transpose
	gettimeofday(&end,NULL);
	printf("End Time: %ld\n", (end.tv_sec * 1000000 + end.tv_usec));

	long difference = ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec));
	printf("Time Difference in MicroSeconds: %ld\n\n", difference);

	//float elems = matrixx * matrixx;

/*
	printf("transposed matrix\n");
	for(int i=0; i<matrix_size*matrix_size; i++){
		if((i!=0) && (i%matrix_size == 0)){
			printf("\n");
		}
		printf("%f ", AT[i]);
	}
	printf("\n");
	
	*/
	free(A);
	free(AT);
	return 0;

}