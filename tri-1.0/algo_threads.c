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
    arguments_t *arguments;
    pthread_t *tids;
    int inf, sup;
    int erreur, i;
    void *status, *args_algo;

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

    for (i=0; i<parallelism; i++)
         pthread_join(tids[i], &status);

    traitement_resultats(parallelism, arguments);

    free(arguments);
    free(tids);
}
