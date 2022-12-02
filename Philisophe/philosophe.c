#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int nb_philosophs = 0;
pthread_mutex_t* baguette; //peut etre construire une structure pour l'init plus loin et pas devoir faire le malloc de la mort plus bas

//pthread_t phil[PHILOSOPHES];
//pthread_mutex_t baguette[PHILOSOPHES];


void mange(int id) {
    printf("Philosophe [%d] mange\n",id);
    for(int i=0;i< rand(); i++) {
        // philosophe mange
    }
}

void* philosophe ( void* arg ){
    int *id=(int *) arg;
    int left = *id;
    int right = (left + 1) % nb_philosophs;
    int i = 0;
    while(i < 100000) {
        // philosophe pense
        if(left<right) {
            pthread_mutex_lock(&baguette[left]);
            printf("Philosophe %d lock baguette %d", arg, left);
            pthread_mutex_lock(&baguette[right]);
            printf("Philosophe %d lock baguette %d", arg, right);

        }
        else {
            pthread_mutex_lock(&baguette[right]);
            printf("Philosophe %d lock baguette %d", arg, right);
            pthread_mutex_lock(&baguette[left]);
            printf("Philosophe %d lock baguette %d", arg, left);
        }
        mange(*id);
        pthread_mutex_unlock(&baguette[left]);
        printf("Philosophe %d unlock baguette %d", arg, left);
        pthread_mutex_unlock(&baguette[right]);
        printf("Philosophe %d unlock baguette %d", arg, right);
        i++;
    }
    return (NULL);
}

int main(int argc, char *argv[]) {

    nb_philosophs = atoi(argv[1]);
    pthread_t phil[nb_philosophs];
    baguette = (pthread_mutex_t*) malloc(nb_philosophs * sizeof(pthread_mutex_t)); //on a pas le nombre de philosophes quand ont init baguette au debut du code, c'est assez caca je sais pas si ça fonctionne

    for (int i = 0; i < nb_philosophs; i++)
    {
        pthread_mutex_init(&baguette[i],NULL);
    }

    for (int j = 0; j < nb_philosophs; j++)
    {
        pthread_create(&phil[j], NULL, &philosophe,(void*) (intptr_t) j);// le dernier argument du pthread_creat est caca je pense 
    }

    for (int k = 0; k < nb_philosophs; k++)
    {
        pthread_join(phil[k], NULL);
    }
    
    for (int l = 0; l < nb_philosophs; l++)
    {
        pthread_mutex_destroy(&baguette[l]);
    }
    
}

