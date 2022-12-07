#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


/*
On favorise les writer ici
*/

pthread_mutex_t m_rcount;
pthread_mutex_t m_wcount;

sem_t wsem; 
sem_t rsem; 

int readcount=0; 
int writecount=0; 

int global_count=0;

void* writer(void* param) {
    int* crap = (int*) param;
    int count = 0;
    while(count < *crap) {
        pthread_mutex_lock(&m_wcount);
        writecount++;
        if(writecount == 1) {
            sem_wait(&rsem); 
        }
        pthread_mutex_unlock(&m_wcount);        

        sem_wait(&wsem); 

        for (int i = 0; i < 10000; i++)
        {
            /* code */
        }
        
        //printf("writer");

        sem_post(&wsem);

        pthread_mutex_lock(&m_wcount);
        writecount--;
        if(writecount == 0) {
            sem_post(&rsem);
        } 
        pthread_mutex_unlock(&m_wcount);
        count++;
    }
    return NULL;
}


void* reader(void* param) {
    int* fnck = (int*) param;
    int x = 0;
    while(x < *fnck) {
        sem_wait(&rsem);
        pthread_mutex_lock(&m_rcount);
        readcount++;
        if (readcount==1) { 
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&m_rcount);
        sem_post(&rsem); 
        for (int i = 0; i < 10000; i++)
        {
            /* code */
        }
        
        //printf("reader");

        pthread_mutex_lock(&m_rcount);
        readcount--;
        if(readcount==0) { 
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&m_rcount);
        x++;
    }
    return NULL;
}

//int main(int argc, char *argv[]){
//
//    printf("why dont you want to work?\n");
//    int fuckyou = atoi(argv[1]);
//    printf("fuckyou: %d\n", fuckyou);
//    return 0;
//}
int main(int argc, char *argv[]) 
{
    //printf("what?");
    int numreaders = atoi(argv[2]);
    int numwriters = atoi(argv[1]);

    sem_init(&wsem, 0, 1);
    sem_init(&rsem, 0, 1);

    pthread_t threads_reader[numreaders];
    pthread_t threads_writer[numwriters];

    pthread_mutex_init(&m_rcount, NULL);
    pthread_mutex_init(&m_wcount, NULL);

    //printf("work0");
    int *to_write = (int *)malloc(sizeof(int));
    *to_write = 640/numwriters; //probleme avec la division TODO
    //printf("to_read before: %d\n", *to_read);

    //printf("work1");
    int *to_write_end = (int *)malloc(sizeof(int));
    *to_write_end = *to_write + 640 - (*to_write * numwriters);

    //printf("work2");
    int *to_read = (int *)malloc(sizeof(int));
    *to_read = 2560/numreaders; //probleme avec la division TODO
    //printf("to_read before: %d\n", *to_read);

    //printf("work3");
    int *to_read_end = (int *)malloc(sizeof(int));
    *to_read_end = *to_read + 2560 - (*to_read * numreaders);
    //printf("to_read_end: %d\n", *to_read_end);

    for(int x = 0; x < numwriters; x++){
 
        if (x == numwriters-1)
        {
            pthread_create(&threads_writer[x], NULL, &writer, to_write);
        }else{
            pthread_create(&threads_writer[x], NULL, &writer, to_write_end);
        }
    }
    //printf("writet threads created");
    // Create the readers 
	for(int i = 0; i < numreaders; i++){
        if (i == numreaders-1)
        {
            pthread_create(&threads_reader[i], NULL, &reader, to_read);
        }else{
            pthread_create(&threads_reader[i], NULL, &reader, to_read_end);
        }
    }

    //printf("reader threads created");
    
    for (int i=0; i<numreaders; i++) {
        pthread_join(threads_reader[i], NULL);
    }
    for (int i=0; i<numwriters; i++) {
        pthread_join(threads_writer[i], NULL);
    }
    return 0;
}