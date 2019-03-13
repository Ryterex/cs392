/* Caleb Obeng
	I pledge my honor that I have abided by the stevens honor system. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command-line arguments\n usage: %s <input filename> <output filename>", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "rb"); //open input file
	FILE *ffp = fopen(argv[2], "w"); //create output file
	unsigned char buffer[8];
	
	//get total number of bytes that need to be read
	long current = 0;
	fseek(fp, 0, SEEK_END);
	long total = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//write all of the binary numbers back to strings
	while(current < total){
		fread(buffer,2,1,fp);
		fprintf(ffp, "%d\t", (buffer[1]<<8) | buffer[0]); //combining bits using bitshifting

		fread(buffer,2,1,fp);
		fprintf(ffp, "%d\t", (buffer[1]<<8) | buffer[0]);

		fread(buffer,1,1,fp);
		fprintf(ffp, "%d\t", (buffer[0]));

		fread(buffer,8,1,fp);
		fprintf(ffp, "%d\n", (((buffer[7]<<24)<<24)<<8) | ((buffer[6]<<24)<<24) | ((buffer[5]<<24)<<16) 
			| ((buffer[4]<<24)<<8) | (buffer[3]<<24) | (buffer[2]<<16) 
			| (buffer[1]<<8) | (buffer[0]));

		current += 13;
	}

	free(buffer);
	fclose(fp);
	fclose(ffp);
	return 0;

}