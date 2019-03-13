#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
	if (argc != 3)
		{fprintf(stderr,"Wrong number of command-line arguments\n");
		//usage(argv[0]);
		return -1;}
	//set the files to be the arguments
	FILE* input = fopen(argv[1],"rb");
	FILE* output = fopen(argv[2],"w");
	if(input==NULL){perror("Error opening file");return -1;}
	fseek(input,0,SEEK_END);
	long fsize=ftell(input);
	fseek(input,0,SEEK_SET);
	/*set buffer that will hold input contents to be size of the
	input file (bytes)*/
	unsigned char* buffer=NULL;
	buffer=malloc(fsize);
	fread(buffer,fsize,1,input);
	//print bytes to outputfile in the right order
	for(int i=0;i<fsize;i+=19){
		fprintf(output,"%d\t",buffer[i] | (buffer[i+1]<<8));
		fprintf(output,"%ld\t",buffer[i+2] | (buffer[i+3]<<8)
					| (buffer[i+4]<<16) | (buffer[i+5]<<24)
					| ((long)buffer[i+6]<<32) | ((long)buffer[i+7]<<40)
					| ((long)buffer[i+8]<<48) | ((long)buffer[i+9]<<56));
		fprintf(output,"%d\t",buffer[i+10]);
		fprintf(output,"%ld\n",buffer[i+11] | (buffer[i+12]<<8)
					| (buffer[i+13]<<16) | (buffer[i+14]<<24)
					| ((long)buffer[i+15]<<32) | ((long)buffer[i+16]<<40)
					| ((long)buffer[i+17]<<48) | ((long)buffer[i+18]<<56));}
	fclose(input);
	fclose(output);
  return 0;}
