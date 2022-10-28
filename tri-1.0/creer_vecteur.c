#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>

void usage(char *commande) {
    fprintf(stderr, "Usage :\n");
    fprintf(stderr, "%s [ --seed number ] [ --size number ] [ --min value ] "
                    "[ --max value ] [ --help ]\n\n", commande);
    fprintf(stderr, "Ce programme affiche sur sa sortie standard la taille "
                    "donnee (defaut 1000) puis autant d'entiers que cette "
                    "taille. Chacun de ces entiers est genere aleatoirement "
                    "dans l'intervalle [min;max] (defaut [0;1000]). Le "
                    "generateur aleatoire est initialise avec la valeur "
                    "donnee pour seed ou, a defaut, avec l'horloge systeme.\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int graine, taille, min, max, i, opt;
    struct option longopts[] = {
        { "help", required_argument, NULL, 'h' },
        { "seed", required_argument, NULL, 'S' },
        { "size", required_argument, NULL, 's' },
        { "min", required_argument, NULL, 'm' },
        { "max", required_argument, NULL, 'M' },
        { NULL, 0, NULL, 0 }
    };

    graine = time(NULL);
    taille = 1000;
    min = 0;
    max = 1000;

    while ((opt = getopt_long(argc, argv, "hs:S:m:M:", longopts, NULL)) != -1) {
        switch (opt) {
          case 'm':
            min = atoi(optarg);
            break;
          case 'M':
            max = atoi(optarg);
            break;
          case 's':
            taille = atoi(optarg);
            break;
          case 'S':
            graine = atoi(optarg);
            break;
          case 'h':
          default:
            usage(argv[0]);
        }
    }
    argc -= optind;
    argv += optind;


    srandom(graine);

    printf("%d\n", taille);
    for (i=0; i<taille; i++)
        printf("%ld\n", (random()%(max-min) + min));
    return 0;
}
