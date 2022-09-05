#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "timer.h"

#define NPROCESS 100

void *f(){
    pthread_exit((void *) 0);
    return NULL;
}


void wait_Thread(int, pthread_t[]); // Définition du prototype de fonction pour l'utiliser

long create_thread(int n) {
    pthread_t contonaire[n];
	struct timespec vartime = timer_start(); /* Démarrage de la mesure temporelle */
	
    /* Création de n threads s'exécutant en parallèle */
    for (int i = 0; i < n; ++i) {
        pthread_t th;

        pthread_create(&th, NULL, f, NULL);
        contonaire[i] = th;
	}
	/* On mesure le temps écoulé pour la création des n processus */
	long time = timer_end(vartime);
	
	/* On attend la fin des threads créés par mesure sociale et pour éviter un impact sur les prochaine mesures */
    wait_Thread(n, contonaire);

	return time; /* Retourne le temps écoulé pour réaliser la création des n processus */
}

void wait_Thread(int n, pthread_t contonaire[]) {
    /* Mesure de salubrité sociale, le père attend la fin de tous ses fils */
    for (int i = 0; i < n; ++i) 
        pthread_join(contonaire[i], NULL);
}

int main(int argc, char *argv[]) {
	int n = NPROCESS;

    for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			n = atoi(argv[i]);
		}
	}
	
	long time_processus = create_thread(n);
	
	printf("Time taken for creating %d processus (nanoseconds): %ld\n", n, time_processus);
	printf("Time taken for creating %d processus (milliseconds): %ld\n", n, time_processus / NANO_TO_MILLI);

    /* On flushe la sortie standard */
    fflush(stdout);

    /* Fin du père */
    exit(0);
}

