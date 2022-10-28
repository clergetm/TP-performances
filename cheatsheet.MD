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
