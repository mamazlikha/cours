#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

void* parcours_5_fois(long n){
	if (n<0)pthread_exit((void *) 1);
	for(int i = 0; i<5; i++){
		printf("pid du processus: %d et le id du thread est: %ld\n ", getpid(), pthread_self());
			printf("Linux Thread ID: %ld\n", syscall(SYS_gettid));
		sleep(n);
	}
	if(n > 0){
		pthread_exit((void *) 0);
		printf("\n");
	}
}


void thread(int n1, int n2){
	long retour;
	pthread_t th1, th2;

	// maintenant on créer 2 threads:

	pthread_create(&th1, NULL, parcours_5_fois, n1);
	pthread_create(&th2, NULL, parcours_5_fois, n1);

	pthread_join(th1, (void*) &retour);	
	pthread_join(th2, (void*) &retour);	
}


int main(int argc, char** argv){
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	thread(n1,n2);
	return 0;
}
