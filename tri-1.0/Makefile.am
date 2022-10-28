AM_CFLAGS=-W -Wall -Werror -g

PRINCIPAL=main.c temps.c algo_principal.h appels_sequentiels.h commun.h temps.h

TRI=tri.c $(PRINCIPAL)

bin_PROGRAMS=creer_vecteur \
             tri_sequentiel tri_threads

creer_vecteur_SOURCES=creer_vecteur.c

tri_threads_SOURCES=algo_threads.c $(TRI)
tri_threads_LDADD=-lpthread

tri_sequentiel_SOURCES=algo_sequentiel.c $(TRI)

test: $(bin_PROGRAMS)
	./creer_vecteur >vecteur.txt
	./tri_sequentiel --time --rusage <vecteur.txt
	./tri_threads --time --rusage --parallelism 4 <vecteur.txt
