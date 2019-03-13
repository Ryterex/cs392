/* Caleb Obeng
	I pledge my honor that I have abided by the stevens honor system. */
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE    5000

/*
int ccount = 0;
void child_handler(int sig){
	int olderrno = errno;
	pid_t pid;
	while((pid=waitpid(-1,NULL, WNOHANG))>0){
		ccount--;
		sio_puts("pid: ");
		sio_putl((long)pid);
		sio_puts("\n");
	}
	if(errno != ECHILD){
		sio_error("wait error");
	}
	errno = olderrno;
} */

//evaluate the command the user is trying to run
void eval(char *command, char directory[PATH_MAX]){
	int bg;
	pid_t pid;
	char *token;
	char *tokens[20];
	//printf("%s", command);

	//tokenize the command, removing spaces and new line character at the end
	int i=0;
	token = strtok(command, "\n");
	token = strtok(token, " ");
	while(token != NULL){
		tokens[i++]=token;
		token = strtok(NULL, " ");
	}

	//cd function
	if(strcmp(tokens[0],"cd")==0){
		//tokens[1] = strtok(tokens[1], "\n");
		//printf("%s\n", tokens[1]);
		if(chdir(tokens[1]) != 0){
			perror("directory change error");
			return;
		}
		printf("directory changed\n");
	}
	//exit function
	else if(strcmp(tokens[0],"exit")==0){
		exit(0);
	}

	//background process
	if(strcmp(tokens[i-1], "&")==0){
		printf("this is a background process\n");
		//printf("number of tokens is %i\n", i);
		tokens[i-1] = NULL;
		i--;
		if((pid = fork()) == 0){ //child process
			if (execvp(tokens[0], tokens) < 0){
				printf("%s: Command not found\n", tokens[0]);
			}
			printf("pid: %d cmd: %s", pid, command);
			return;
		}
		//parent process
		int status;
		if(waitpid(pid, &status, 0)<0){
			perror("waitpid error");
		}
		printf("supposed to reap children\n");
		return;

	}
	else{//no background process needed
		if((pid = fork()) == 0){
			if (execvp(tokens[0], tokens) < 0){
				printf("%s: Command not found\n", tokens[0]);
			}
			return;
		}
		int status;
		if(waitpid(pid, &status, 0)<0){
			perror("waitpid error");
		}
		return;
	}

	return;
}

int main(int argc, char **argv){
	if (argc != 1) {
		fprintf(stderr, "Function takes no arguments\n");
		return -1;
	}

	uid_t uid = getuid();

	struct passwd *pwuid = getpwuid(uid); //user id

	char directory[PATH_MAX]; //directory

	if (getcwd(directory, sizeof(directory)) == NULL) {
       //printf("Current working dir: %s\n", directory);
		perror("Error getting directory");
		return 1;
   	} 
/*	else {
		perror("Error getting directory");
		return 1;
	}*/

	char line[MAXLINE];
	while (1) { //function runs continuously until error or exit
	/* read */
	if (getcwd(directory, sizeof(directory)) == NULL) {
       //printf("Current working dir: %s\n", directory);
		perror("Error getting directory");
		return 1;
   	} 
	printf("SWS:%s:%s> ", pwuid->pw_name, directory);
	fgets(line, MAXLINE, stdin);

	if(feof(stdin)){
		exit(0);
	}
	/* evaluate */

	eval(line, directory);

	}

	return 0;

}