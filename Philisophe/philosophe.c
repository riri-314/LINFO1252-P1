#include <pthread.h>
#include <stdio.h>
// pour le atoi
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
// pour le memcopy
#include <string.h>

int nb_philosophs = 0;
int nb_baguettes = 0;
pthread_mutex_t *baguette; // peut etre construire une structure pour l'init plus loin et pas devoir faire le malloc de la mort plus bas

// pthread_t phil[PHILOSOPHES];
// pthread_mutex_t baguette[PHILOSOPHES];

void mange(int id)
{
    //printf("Philosophe [%d] mange\n", id);
    return;
}

void *philosophe(void *arg)
{
    int *id = (int *)arg;
    int left = *id;
    //printf("left: %d\n", left);

    int right = (left + 1) % nb_baguettes; // si garde nb_philosophe ça marche pas pour arg = 1, modulo 1 égale toujours 0 donc left = right = 0 = probleme
    //printf("right: %d\n", right);

    for (int i = 0; i < 100000; i++)
    {
        // philosophe pense
        if (left < right)
        {
            pthread_mutex_lock(&baguette[left]);
            //printf("Philosophe %d lock baguette %d\n", *id, left);
            pthread_mutex_lock(&baguette[right]);
            //printf("Philosophe %d lock baguette %d\n", *id, right);
        }
        else
        {
            pthread_mutex_lock(&baguette[right]);
            //printf("Philosophe %d lock baguette %d\n", *id, right);
            pthread_mutex_lock(&baguette[left]);
            //printf("Philosophe %d lock baguette %d\n", *id, left);
        }
        mange(*id);
        pthread_mutex_unlock(&baguette[left]);
        // printf("Philosophe %d unlock baguette %d", arg, left);
        pthread_mutex_unlock(&baguette[right]);
        // printf("Philosophe %d unlock baguette %d", arg, right);
        i++;
    }
    //printf("Return %d\n", *id);
    return (NULL);
}

int main(int argc, char *argv[])
{

    nb_philosophs = atoi(argv[1]);
    nb_baguettes = nb_philosophs;

    if (nb_baguettes == 1) //si 1 seul philosophe bah il lui faut 2 baguettes et pas 1 sinon bug avec thread = 1
    {
        nb_baguettes += 1;
        //printf("nb_baguette: %d\n",nb_baguettes);
    }

    pthread_t phil[nb_philosophs];
    baguette = (pthread_mutex_t *)malloc(nb_baguettes * sizeof(pthread_mutex_t)); // on a pas le nombre de philosophes quand ont init baguette au debut du code, c'est assez caca je sais pas si ça fonctionne

    for (int i = 0; i < nb_baguettes; i++)
    {
        pthread_mutex_init(&baguette[i], NULL); //devrait check si mutex est bien fait 
        //printf("i: %d\n", i);
    }

    for (int j = 0; j < nb_philosophs; j++)
    {
        int *n = (int *)malloc(sizeof(int)); //serait mieux de passer un pointeur vers une structure dans pthread creat mais ça marche comme ça. La free du maloc doit se faire dans philosophe
        *n = j;
        pthread_create(&phil[j], NULL, &philosophe, (void *) n); //(void*) (intptr_t) j
        //printf("j: %d\n", j);
    }

    for (int k = 0; k < nb_philosophs; k++)
    {
        //printf("k_b: %d\n", k);
        pthread_join(phil[k], NULL); //devrait check si join est bien fait 
        //printf("k_a: %d\n", k);
    }

    for (int l = 0; l < nb_philosophs; l++)
    {
        pthread_mutex_destroy(&baguette[l]); //devrait check si destroy est bien fait 
        //printf("l: %d\n", l);
    }
}
