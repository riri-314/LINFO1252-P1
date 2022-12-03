#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

void *producer (void *) ;
void *consumer(void *) ;
sem_t empty, full, mutex ;


void main(int argc, char *argv[]) {
    
    int nb_consumers = atoi(argv[1]);
    int nb_producers = atoi(argv[2]);
    
    pthread_t cons[nb_consumers];
    pthread_t prod[nb_producers];
    
    pthread_mutex_t buffer;
    pthread_mutex_init(&buffer, NULL);

    sem_init(&empty, 0, 8) ;
    sem_init(&full, 0, 0) ;
    sem_init(&mutex, 0, 1) ;

    int *to_produce = (int *)malloc(sizeof(int));
    *to_produce = 8192/nb_producers; //probleme avec la division TODO

    for (int i = 0; i < nb_producers; i++)
    {
        pthread_create(&prod[i], NULL, &producer, (void *) to_produce);
    }

    int *to_consume = (int *)malloc(sizeof(int));
    *to_consume = 8192/nb_consumers; //probleme avec la division TODO

    for (int i = 0; i < nb_consumers; i++)
    {
        pthread_create(&cons[i], NULL, &consumer, (void *) to_consume);
    }

    for (int i = 0; i < nb_producers; i++)
    {
        pthread_join(prod[i], NULL);
    }
    
    for (int i = 0; i < nb_consumers; i++)
    {
        pthread_join(cons[i], NULL);
    }
}

void *producer(void *arg) {
    sem_wait(&empty);
    sem_wait(&mutex);
    
    sem_post(&mutex);
    sem_post(&full);

 }

void *consumer (void *arg) {
    sem_wait(&full);
    sem_wait(&mutex);
    
    sem_post(&mutex);
    sem_post(&empty);
    
}