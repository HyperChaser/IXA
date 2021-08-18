#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	DIR *dir;
	struct dirent *ptr;
	dir = opendir(".");
	
	if (dir == NULL){
		printf("open failure");	
		exit(1);
	}
	while((ptr = readdir(dir))!=NULL){
		
		printf(">> %s\n",ptr->d_name);
	};
	
	
	closedir(dir);
	return 0;
}
