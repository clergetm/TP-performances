#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "algo_principal.h"
#include "appels_sequentiels.h"

void *comportement_thread(void *arg) {
    traitement((arguments_t *) arg);
    pthread_exit(NULL);
}

void algo_principal(int parallelism, int *tableau, int taille, char *arg)
{
    struct timeval temps1, temps2;
    arguments_t *arguments;
    pthread_t *tids;
    int inf, sup;
    int erreur, i;
    void *status, *args_algo;

    gettimeofday(&temps1, NULL); // Obtenir temps initial

    args_algo = initialisation(parallelism, tableau, taille, arg);

    tids = malloc(parallelism*sizeof(pthread_t));
    arguments = malloc(parallelism*sizeof(arguments_t));
    if ((tids == NULL) || (arguments == NULL)) {
        fprintf(stderr, "Impossible d'allouer les structures de gestion des "
                        "threads\n");
        exit(1);
    }

    inf = 0;
    sup = (taille-1) / parallelism;

    for (i=0; i<parallelism; i++) {
        arguments[i].num = i;
        arguments[i].inf = inf;
        arguments[i].sup = sup;
        arguments[i].tableau = tableau;
        arguments[i].taille = taille;
        arguments[i].args_algo = args_algo;

        erreur = pthread_create(&tids[i], NULL, comportement_thread,
                                &arguments[i]);
        if (erreur != 0) {
            fprintf(stderr, "Erreur de creation du thread %d\n", i);
            exit(1);
        }
        inf = sup+1;
        sup = ((i+2)*(taille-1)) / parallelism;
         
        }
    gettimeofday(&temps2, NULL); // Obtenir temps après création
    printf("Le temps de création des threads : %ld.%lds\n",temps2.tv_sec-temps1.tv_sec,temps2.tv_usec-temps1.tv_usec);

    for (i=0; i<parallelism; i++)
        pthread_join(tids[i], &status);
    gettimeofday(&temps2, NULL); // Obtenir temps après éxécution
    printf("Le temps d’éxécution des threads : %ld.%lds\n",temps2.tv_sec-temps1.tv_sec,temps2.tv_usec-temps1.tv_usec);
    
    traitement_resultats(parallelism, arguments);

    free(arguments);
    free(tids);
}
