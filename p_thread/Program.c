#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *myfunc(void *myvariable){
	char *variable = (char *)myvariable;
	int i;
	for (i=0;i<10;i++){
		printf("%s , %d \n",variable,i);
	}
}
int main(int argc, char *argv[]){
	int ret1,ret2;
	pthread_t thread1,thread2;
	char *msg1 = "first thread";
	char *msg2 = "second thread";
	ret1 = pthread_create(&thread1,NULL,myfunc,(void *)(msg1));
	ret2 = pthread_create(&thread2,NULL,myfunc,(void *)(msg2));
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("my app after pthread_create \n");
	return 0;
}
