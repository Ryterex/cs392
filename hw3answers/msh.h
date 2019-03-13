#ifndef MSH_H_
#define MSH_H_
#endif

void child_handler(int sig);
void siginthandler();
void eval(char *command, char directory[PATH_MAX]);
