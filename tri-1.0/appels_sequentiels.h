#ifndef __APPELS_SEQUENTIELS__
#define __APPELS_SEQUENTIELS__

/* Structure passee a chaque participant au calcul contenant son numero, les
 * bornes de l'intervalle d'indices sur lequel il travaille, le tableau
 * d'elements, la taille du tableau et les arguments construits par l'appel a
 * initialisation */
typedef struct {
    int num;
    int inf, sup;
    int *tableau;
    int taille;
    void *args_algo;
} arguments_t;

/* Fonction appelee dans le programme principal avant creation des threads
 * Initialise les structures de donnees propre a l'algo et renvoie un pointeur
 * sur ces structures
 * Les arguments sont :
 * - le degre de parallelisme (nombre de thread, ==0 pour un algo sequentiel)
 * - le tableau d'elements et sa taille
 * - l'argument passe en ligne de commande (ou NULL si aucun argument) */
void *initialisation(int parallelism, int *tableau, int taille, char *arg);

/* Fonction appelee dans chaque thread (traitement effectue en parallele) avec
 * en argument la structure decrite au debut de ce fichier */
void traitement(arguments_t *args);

/* Fonction appelee dans le programme principal apres terminaison des threads
 * Les arguments sont :
 * - le degre de parallelisme
 * - le tableau des structures passees a chacun des threads lors du calcul (ce
 *   tableau contient min(1, parallelism) structures correspondantes au modele
 *   decrit au debut de ce fichier) */
void traitement_resultats(int parallelism, arguments_t *args);

#endif
