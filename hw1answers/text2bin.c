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

	FILE *fp = fopen(argv[1], "r"); //open input file
	FILE *ffp = fopen(argv[2], "wb"); //create output file
	char tab[] = "\t";
	char *buffer = NULL;
	size_t buffersize = 0;
	char *token;
	char *tokens[4];
	if (fp == NULL){
		perror("Error opening file.");
		return -1;
	}

	//split the numbers by tabs then write them in binary
	while(getline(&buffer,&buffersize,fp)!=-1){
		//printf("%s\n", buffer);

		int i=0;
		char line[200];
		strcpy(line,buffer);
		token = strtok(line, tab);
		while(token != NULL){
			tokens[i++]=token;
			token = strtok(NULL, tab);
		}
		short one = atoi(tokens[0]);
		short two = atoi(tokens[1]);
		char three = atoi(tokens[2]);
		long long four = atoll(tokens[3]);

		
		fwrite(&one,2,1,ffp);
		fwrite(&two,2,1,ffp);
		fwrite(&three,1,1,ffp);
		fwrite(&four,8,1,ffp);

	}

	free(buffer);
	fclose(fp);
	fclose(ffp);
	return 0;

}