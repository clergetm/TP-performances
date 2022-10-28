#include "appels_sequentiels.h"
#include "commun.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compar(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

void *initialisation(int parallelism, int *tableau, int taille, char *arg) {
    (void) parallelism;
    (void) tableau;
    (void) taille;
    (void) arg;
    return NULL;
}

void traitement(arguments_t *args) {
    qsort(args->tableau + args->inf, args->sup - args->inf + 1, sizeof(int),
          compar);
}

void traitement_resultats(int parallelism, arguments_t *args) {
    int i, j, min;

    /* Ici on fusionne les sous tableaux tries */
    if (parallelism > 1) {
        int *resultat;
        resultat = malloc(sizeof(int)*args->taille);
        if (resultat == NULL) {
            fprintf(stderr, "Impossible d'allouer le tableau resultat\n");
            exit(1);
        }

        /* Remarquons que le coût de cette fusion est en parallelisme*taille */
        for (i=0; i<args->taille; i++) {
            min = -1;
            for (j=0; j<parallelism; j++)
                if ((args[j].inf <= args[j].sup) && ((min == -1) ||
                   (args->tableau[args[j].inf] < args->tableau[args[min].inf])))
                    min = j;
            resultat[i] = args->tableau[args[min].inf++];
        }
        memcpy(args->tableau, resultat, sizeof(int)*args->taille);
    }

}
