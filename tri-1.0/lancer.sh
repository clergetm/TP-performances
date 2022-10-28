#!/bin/bash

#nb d'itérations pour chaque expérience
ITERATIONS=30
FILE=$1
FILEWITHPATH=vecteurs/$FILE.vect
RESPATH=vecteurs/res/$FILE

# lancement du pg séquentiel
# attention à l'option -q = quiet
for i in `seq 1 ${ITERATIONS}`;
do
	echo SEQUENTIAL $i .........................
	./tri_sequentiel < $FILEWITHPATH -t -q >> $RESPATH/seq-$FILE.res
done

# # lancement du programme parallèle
# for THREADS in 2 4 8 16 32 64;
# do
#     echo PARALLEL NB THREADS = $THREADS ...............	       
#     for i in `seq 1 ${ITERATIONS}`;
#     do
# 	echo $i 
# 	./tri_threads < $FILEWITHPATH -t -q -p $THREADS >> $RESPATH/par-$FILE-$THREADS.res
#     done
# done    

