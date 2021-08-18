#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd;
	int buf[10]={1,2,3,4,5,6,7,8,9,10};
	float num_float=5.2;
	printf("num float = %f",num_float);
	printf("num float = %b",num_float);
	fd = open("file",O_CREAT | O_APPEND | O_RDWR, 0600);
	if(fd<0)
		{
		perror("openerror");
		exit(1);
		}
	
	return 0;
}
