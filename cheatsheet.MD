# Créer les 3 vecteurs nécessaires.

./creer_vecteur --size 1000 petit_vecteur
./creer_vecteur --size 1000000 moyen_vecteur
./creer_vecteur --size 1000000000 grand_vecteur

# Lancer les tris 

## Parallèle
./tri_threads -p 100 -q < petit_vecteur

## Séquentiel
./tri_sequentiel -q < petit_vecteur

## Tous
echo "parallèle" && ./tri_threads -p 100 -q < petit_vecteur && echo "sequentiel" && ./tri_sequentiel -q < petit_vecteur

# lancer.sh
./lancer.sh petit_vecteur

./lancer.sh moyen_vecteur

./lancer.sh grand_vecteur

# Calcul des accélérations. 
## Regex notepad++ afin d’obtenir la somme:

Pour transformer (par exemple) le fichier par-moyen_vecteur-64.res:
- à partir d`‘un fichier de 150 lignes de consoles`
- pour obtenir: ` une addition de tous les timeofday`

Voici les étapes à suivre:
1. `Le temps de rusage user       est : ([0.9]+).[0-9]+s   ` to  `''`
2. `Le temps de rusage user       est : 0.0s               ` to  `''`
3. `Le temps de rusage superuser  est : ([0.9]+).[0-9]+s   ` to  `''`
4. `Le temps de création des threads : ([0.9]+).[0-9]+s    ` to  `''`
5. `Le temps d’éxécution des threads : ([0.9]+).[0-9]+s    ` to  `''`
6. `Le temps d’éxécution des threads : 1.0s                ` to  `''`
7. `Le temps de timeofday         est :                    ` to  `''`
8. `-([0-9]+)                                              ` to  `0`
9. `\r\n                                                   ` to  `''`
10. `s                                                     ` to  `+`
11. Finally: remove the last + from the line.
