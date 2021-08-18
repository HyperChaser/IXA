#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int childpid;
	int countchild=0,countparrent=0;
	printf("before the fork\n");
	childpid = fork();
	if(childpid==0){
		while(countchild<20){
			countchild++;
			printf("child %d \n",countchild);
			sleep(1);
		}
		}
	else{
		while(countparrent <20)
		{
			countparrent++;
			printf("parrent %d \n",countparrent);
			sleep(1);
		}
	}
	
	return 0;
}
