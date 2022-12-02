#!/bin/bash

make clean
make 

echo "nb_mesure, nb_threads, time" &> philosophe.csv #ajouter nom dans les colones du csv

for nb_threads in 1 2 4 8 16 32 64 
do #iterer sur le nombre de threads
    echo "$nb_threads"
    for nb_mesures in 1 2 3 4 5 
    do #iterer sur le nombre de mesures
    time=$(/usr/bin/time -f "%E" 2>&1 ./philosophe $nb_threads | grep "\.") #trouvé sur internet, peut etre pas la meilleur solution pour mesurer le temps
    echo "$nb_mesures,$nb_threads,$time" >> philosophe.csv
    done
done

make clean
