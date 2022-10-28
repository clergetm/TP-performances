#!/bin/bash

#nb d'itérations pour chaque expérience
ITERATIONS=30
FILE=$1

# lancement du pg séquentiel
# attention à l'option -q = quiet
for i in `seq 1 ${ITERATIONS}`;
do
	echo SEQUENTIAL $i .........................
	./tri_sequentiel < $FILE -t -q >> seq-$FILE.res
done

# lancement du programme parallèle
for THREADS in 2 4 8 16 32 64;
do
    echo PARALLEL NB THREADS = $THREADS ...............	       
    for i in `seq 1 ${ITERATIONS}`;
    do
	echo $i 
	./tri_threads < $FILE -t -q -p $THREADS >> par-$FILE-$THREADS.res
    done
done    

