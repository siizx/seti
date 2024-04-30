#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

int n = 50;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *print_thread(void *k){

	pthread_mutex_lock(&mutex);

	char *c = (char *)k;
	for(int i = 0; i<n; i++){
		printf("%c ", *c);
	}
	
	printf("\n");
	
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(){

	char car = '-';
	char car2 = '@';
	
	pthread_t t1, t2;

	int rc1 = pthread_create(&t1, NULL, print_thread, &car);
	int rc2 = pthread_create(&t2, NULL, print_thread, &car2);

	pthread_join(t1,NULL);
	pthread_join(t2, NULL);

	return 0;
}
