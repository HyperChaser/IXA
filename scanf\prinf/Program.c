#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define MINORBITS	20
#define MINORMASK	((1U << MINORBITS) - 1)
int main(int argc, char *argv[]){
	char msg[15]="gkeconmemay";
	//char *buffer=msg;
	//scanf("input buffer",buffer);
	memset(msg,'$',5);
	printf("buffer is %s",msg);
//	printf("buffer is %d",sizeof(buffer));
	//printf("buffer is %x",msg);
}
