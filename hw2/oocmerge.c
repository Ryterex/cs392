/* Caleb Obeng
	I pledge my honor that I have abided by the stevens honor system. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "oocmerge.h"


//merge for an even number of files
void mergeeven( int number, char files[number][16]){
	if (number == 1){
		return;
	}
	printf("I am now merging %i files,\n", number);

	int j = 0;
	if(number % 2 != 0){
		char temps[(number+1)/2][16];
		FILE *result;
		for(int i=0; i<number-1; i+=2){
			printf("%s\t", files[i]);
			printf("%s\n", files[i+1]);
			FILE *temp1 = fopen(files[i], "rb"); //first set of numbers

			if (temp1 == NULL){
				perror("Error opening file.");
				return;
			}
			FILE *temp2 = fopen(files[i+1], "rb"); //second set of numbers

			if (temp2 == NULL){
				perror("Error opening file.");
				return;
			}

			result = fopen("temp.txt", "wb"); //output file to hold the sorted numbers

			long current1 = 0;
			long current2 = 0;

			fseek(temp1, 0, SEEK_END);
			long total1 = ftell(temp1); //total number of bytes in file 1
			fseek(temp1, 0, SEEK_SET);

			fseek(temp2, 0, SEEK_END);
			long total2 = ftell(temp2); //total number of bytes in file 2
			fseek(temp2, 0, SEEK_SET);


			float x; //first number
			fread(&x, sizeof(float), 1, temp1);


			float y; //second number
			fread(&y, sizeof(float), 1, temp2);


			//while neither file is at the end
			while(current1 < total1 && current2 < total2){
				if(x<y){
					fwrite(&x, sizeof(float), 1, result);
					fread(&x, sizeof(float), 1, temp1);
					current1 += 4;
				}
				else{
					fwrite(&y, sizeof(float), 1, result);
					fread(&y, sizeof(float), 1, temp2);
					current2 += 4;
				}
			}
			//end of first file first
			if(current1 == total1){
				while( current2 < total2){
					fwrite(&y, sizeof(float), 1, result);
					fread(&y, sizeof(float), 1, temp2);
					current2 +=4;
				}
			}
			//end of second file first
			else{
				while(current1<total1){
					fwrite(&x, sizeof(float), 1, result);
					fread(&x, sizeof(float), 1, temp1);
					current1 +=4;
				}
			}
			fclose(temp1);
			fclose(temp2);
			fclose(result);
			//remove(files[i+1]);
			FILE *results = fopen("temp/temp.txt", "rb");
			if (results == NULL){
				perror("Error opening file.");
				return;
			}
			FILE *answer = fopen(files[i], "wb");


			long current = 0;
			fseek(results, 0, SEEK_END);
			long total = ftell(results);
			printf("results total: %ld\n", total);
			fseek(results, 0, SEEK_SET);

			while(current < total){
				float z;
				fread(&z, sizeof(float), 1, results);
				printf("z = %f\n", z);
				fwrite(&z, sizeof(float), 1, answer);
				current += 4;
			}

			fclose(results);
			char buffer[16];
			sprintf(buffer, files[i]);
			strcpy(temps[j], buffer);
			j++;
			fclose(answer);
		}
		strcpy(temps[((number+1)/2) - 1], files[number-1]);
		//printf("%s", temps[((number+1)/2) - 1]);
		mergeeven( (number+1)/2,temps);
	}
	else{
		char temps[number/2][16];
		FILE *result;
		for(int i=0; i<number; i+=2){
			FILE *temp1 = fopen(files[i], "rb"); //first set of numbers
			if (temp1 == NULL){
				perror("Error opening file.");
				return;
			}
			FILE *temp2 = fopen(files[i+1], "rb"); //second set of numbers
			if (temp2 == NULL){
				perror("Error opening file.");
				return;
			}
			result = fopen("temp/temp.txt", "wb"); //output file to hold the sorted numbers

			long current1 = 0;
			long current2 = 0;

			fseek(temp1, 0, SEEK_END);
			long total1 = ftell(temp1); //total number of bytes in file 1

			fseek(temp1, 0, SEEK_SET);

			fseek(temp2, 0, SEEK_END);
			long total2 = ftell(temp2); //total number of bytes in file 2
			fseek(temp2, 0, SEEK_SET);


			float x; //first number
			fread(&x, sizeof(float), 1, temp1);
			printf("x = %f\n", x);


			float y; //second number
			fread(&y, sizeof(float), 1, temp2);
			printf("y = %f\n", y);

			//while neither file is at the end
			while(current1 < total1 && current2 < total2){
				if(x<y){
					fwrite(&x, sizeof(float), 1, result);
					fread(&x, sizeof(float), 1, temp1);
					current1 += 4;
				}
				else{
					fwrite(&y, sizeof(float), 1, result);
					fread(&y, sizeof(float), 1, temp2);
					current2 += 4;
				}
			}
			//end of first file first
			if(current1 == total1){
				while( current2 < total2){
					fwrite(&y, sizeof(float), 1, result);
					fread(&y, sizeof(float), 1, temp2);
					current2 +=4;
				}
			}
			//end of second file first
			else{
				while(current1<total1){
					fwrite(&x, sizeof(float), 1, result);
					fread(&x, sizeof(float), 1, temp1);
					current1 +=4;
				}
			}
			fclose(temp1);
			fclose(temp2);
			fclose(result);
			//remove(files[i+1]);
			FILE *results = fopen("temp/temp.txt", "rb");
			if (results == NULL){
				perror("Error opening file.");
				return;
			}
			FILE *answer = fopen(files[i], "wb");

			long current = 0;
			fseek(results, 0, SEEK_END);
			long total = ftell(results);
			fseek(results, 0, SEEK_SET);

			while(current < total){
				float z;
				fread(&z, sizeof(float), 1, result);
				fwrite(&z, sizeof(float), 1, answer);
				current += 4;
			}
			fclose(results);
			char buffer[16];
			sprintf(buffer, files[i]);
			strcpy(temps[j],buffer);
			j++;
			fclose(answer);
		}
		mergeeven(number/2,temps);
	}

	printf("I am done merging.\n");
}

//verify that the output file is correct
int verify(char *output){
	FILE *open = fopen(output, "rb");
	if (open == NULL){
		perror("Error opening file.");
		return -1;
	}

	long current = 0;
	fseek(open, 0, SEEK_END);
	long total = ftell(open);
	fseek(open, 0, SEEK_SET);

	while(current < total){

		float x;
		fread(&x, sizeof(float), 1, open);
		float y;
		fread(&x, sizeof(float), 1, open);
		if(x>y){
			fprintf(stderr, "The merge did not execute correctly.");
			return -1;
		}
		else{
			fseek(open, current + 4, SEEK_SET);
			current += 4;
		}
	}
	printf("It worked!!!");
	fclose(open);
	return 0;
}

//delete all files but the files we want to keep
void deleteAll(int N){
	char buffer[16];
	for(int i=1; i<N; i++){
		sprintf(buffer, "array%d.dat", i);
		remove(buffer);
	}
	remove("temp.txt");
}

int main(int argc, char **argv){

	if (argc != 3) {
		fprintf(stderr, "Wrong number of command-line arguments\n usage: ./oocmerge <N> <output filename>");
		return -1;
	}

	//make the directory
	mkdir("temp", 0700);

	int N = atoi(argv[1]);
	//FILE *output = fopen(argv[2], "wb");

	if(N == 0){
		fprintf(stderr, "Can't sort zero numbers.");
		return -1;
	}

	char files[N][16]; //array to store the files being used
	char buffer[16];
	srand(time(NULL));
	char temps[N/2][16];

	FILE *filed;
	//create the random floats then write them to their own files
	for(int i=0; i<N; i++){
		float x = (float)( (rand()) / (float)RAND_MAX);
		float y = (-100 + x * ( 100 + 100 ));
		printf("number %i is %f\n", i, y);
		sprintf(buffer, "array%d.dat", i);
		filed = fopen(buffer, "wb");
		fwrite(&y, sizeof(float), 1, filed);

		strcpy(files[i], buffer);
		printf("f %i is %s\n", i, files[i]);
		fclose(filed);
	}

	
	//do the merging sort

	mergeeven(N, files);

	FILE *outtie = fopen("array0.dat", "rb");
	if (outtie == NULL){
		perror("Error opening file.");
		return -1;
	}
	fseek(outtie, 0, SEEK_END);
	long total = ftell(outtie);
	printf("%ld\n", total);
	fseek(outtie, 0, SEEK_SET);
	for(int i=0; i<N; i++){
		float x;
		fread(&x, sizeof(float), 1, outtie);
		printf("number %i is %f\n", i, x);
	}
	fclose(outtie);

	char *output = argv[2];
	rename("array0.dat", "temp/%s", output);
	printf("\nfilename has been changed");


	verify(output);
	deleteAll(N);

	return 0;
}