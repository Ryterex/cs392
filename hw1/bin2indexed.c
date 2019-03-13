	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if (argc != 4) {
		fprintf(stderr, "Wrong number of command-line arguments\n usage: %s <binary file> <item file> <output filename>", argv[0]);

		return -1;
	}

	FILE *inputf = fopen(argv[1], "rb");
	FILE *itemf = fopen(argv[2], "r");
	FILE *outputf = fopen(argv[3], "wb");

	if (inputf == NULL){
		perror("Error opening first argument.");
		return -1;
	}

	if (itemf == NULL){
		perror("Error opening second argument.");
		return -1;
	}

	char *buffer = NULL;
	size_t buffersize = 0;
	long maxi = 1900;
	long *offset = (long *) malloc(maxi*sizeof(long));
	long i = 1;

	offset[0] = 0;
	offset[1] = 0;

	buffer = NULL;
	buffersize = 0;
	//store all of the offsets for u.item in an array called offset

	while(getline(&buffer,&buffersize,itemf)!=-1){

		if(i+1 == maxi){
			maxi += 1900;
			offset = (long *) realloc(offset, maxi*sizeof(long) + i*sizeof(long));
		}

		long oofs = ftell(itemf);
		offset[i+1] = oofs - i + 1;
		i++;

	}

	//writing to the output file

	unsigned char bufferbinary[8];
	long current = 0;
	fseek(inputf, 0, SEEK_END);
	long total = ftell(inputf);
	fseek(inputf, 0, SEEK_SET);

	while(current < total){
		fread(bufferbinary,2,1,inputf);
		fwrite(bufferbinary, 2, 1, outputf);

		fread(bufferbinary,2,1,inputf);
		short two = (bufferbinary[1]<<8) | bufferbinary[0];
		fwrite(&offset[two],8,1,outputf);

		fread(bufferbinary,1,1,inputf);
		fwrite(bufferbinary, 1, 1, outputf);


		fread(bufferbinary,8,1,inputf);
		fwrite(bufferbinary, 8, 1, outputf);

		current += 13; 
	}

	free(offset);
	fclose(inputf);
	fclose(itemf);
	fclose(outputf);
	return 0;
}