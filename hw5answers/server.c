/* Caleb Obeng
	I pledge my honor that I have abided by the stevens honor system. */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 5000
#define LISTENQ 1024

int open_listenfd(char *port){
	struct addrinfo hints, *listp, *p;
	int listenfd, optval=1;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);

	for (p = listp; p; p = p->ai_next){
		if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
			continue;
		}
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval, sizeof(int));
		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0){
			break;
		}
		close(listenfd);
	}

	freeaddrinfo(listp);
	if (!p){
		return -1;
	}

	if (listen(listenfd, LISTENQ) < 0){
		close(listenfd);
		return -1;
	}
	return listenfd;
}
//int echo(int connfd){
void echo(int connfd){
	size_t n;
	char buf[MAXLINE];
	float sum;
	//float number = atof(buf);
	//sum = number + sum;
	//sprintf(buf, "%f", sum);

	while((n =  read (connfd, buf, MAXLINE)) != 0){
		//printf("Server received %d bytes\n", (int)n);
		float number = atof(buf);
		sum += number;
		write(connfd, "The Sum is now ", 15);
		//printf("The Sum is now ");
		sprintf(buf, "%f", sum);
		//printf("The Sum is now ");
		write(connfd, buf, strlen(buf));
		//write(connfd, "\n", 2);
		memset(buf, 0, MAXLINE);
	}
	//return sum;
}

int main(int argc, char **argv){
	int listenfd, connfd;
	//float sum = 0;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];

	listenfd = open_listenfd(argv[1]);
	while(1){
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (struct sockaddr * restrict)&clientaddr, &clientlen);
		getnameinfo((const struct sockaddr *) &clientaddr, clientlen, client_hostname, MAXLINE,
			client_port, MAXLINE, 0);
		printf("Connected to (%s, %s)\n", client_hostname, client_port);
		echo(connfd);
		//echo(connfd, sum);
		//sum = echo(connfd, sum);
		//printf("Sum: %f", sum);
		close(connfd);
	}
	exit(0);
}