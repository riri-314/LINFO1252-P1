#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h> // for the memset

void *producer (void *) ;
void *consumer(void *) ;
sem_t empty, full, mutex ;
//int produced = 0;
int buffer[8];
int in = 0;
int out = 0;


void main(int argc, char *argv[]) {
    
    int nb_consumers = atoi(argv[2]);
    int nb_producers = atoi(argv[1]);
    
    pthread_t cons[nb_consumers];
    pthread_t prod[nb_producers];

    memset(buffer, 0, 8*sizeof(int));

    //pthread_mutex_t buffer;
    //pthread_mutex_init(&buffer, NULL);

    sem_init(&empty, 0, 8) ;
    sem_init(&full, 0, 0) ;
    sem_init(&mutex, 0, 1) ;

    int *to_produce = (int *)malloc(sizeof(int));
    *to_produce = 8192/nb_producers; //probleme avec la division TODO
    //printf("to_produce before: %d\n", *to_produce);

    int *to_produce_end = (int *)malloc(sizeof(int));
    *to_produce_end = *to_produce + 8192 - (*to_produce * nb_producers);
    //printf("to_produce_end: %d\n", *to_produce_end);

    for (int i = 0; i < nb_producers; i++)
    {
        if (i == nb_producers-1)
        {  
            pthread_create(&prod[i], NULL, &producer, (void *) to_produce_end);
            //printf("thread prod %d created with %d cycle to do\n", i, *to_produce_end);

        }
        else
        {
            pthread_create(&prod[i], NULL, &producer, (void *) to_produce);
            //printf("thread prod %d created with %d cycle to do\n", i, *to_produce);
        }
    }

    int *to_consume = (int *)malloc(sizeof(int));
    *to_consume = 8192/nb_consumers; //probleme avec la division TODO
    //printf("to_consume before: %d\n", *to_consume);

    int *to_consume_end = (int *)malloc(sizeof(int));
    *to_consume_end = *to_consume + 8192 - (*to_consume * nb_consumers);
   // printf("to_consume_end: %d\n", *to_consume_end);

    for (int i = 0; i < nb_consumers; i++)
    {
        if (i == nb_consumers-1)
        {  
            pthread_create(&cons[i], NULL, &consumer, (void *) to_consume_end);
            //printf("thred cons %d created with %d cycle to do\n", i, *to_consume_end);
        }
        else
        {
            pthread_create(&cons[i], NULL, &consumer, (void *) to_consume);
            //printf("thred cons %d created with %d cycle to do\n", i, *to_consume);
        }
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
    int* to_produce = (int*)arg;
    for (int i = 0; i < *to_produce; i++)
    {
        for (int j = 0; j < 10000; j++){
        }
        printf("Pre_Producing: %d\n", i);
        
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = 1;
        in = (in+1)%8;
        //printf("Producing: %d\n", i);

        sem_post(&mutex);
        sem_post(&full);

    }
    return (NULL);

 }

void *consumer (void *arg) {
    int* to_consume = (int*)arg;
    for (int i = 0; i < *to_consume; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        buffer[out] = 0;
        out = (in+1)%8;
        //printf("consuming: %d\n", i);

        sem_post(&mutex);
        sem_post(&empty);
        
        for (int j = 0; j < 10000; j++){
        }
    }
    //printf("finish consuming\n");
    return (NULL);
}