#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "algo_principal.h"
#include "appels_sequentiels.h"

void algo_principal(int parallelism, int *tableau, int taille, char *arg)
{
    void *args_algo;
    arguments_t args;

    (void) parallelism;
    args_algo = initialisation(0, tableau, taille, arg);
    args.num = 0;
    args.inf = 0;
    args.sup = taille-1;
    args.tableau = tableau;
    args.taille = taille;
    args.args_algo = args_algo;

    traitement(&args);

    traitement_resultats(0, &args); 
}
