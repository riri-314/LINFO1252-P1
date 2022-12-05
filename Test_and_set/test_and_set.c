
// pour le atoi
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int nb_threads = 0;
int lock_int = 0;

void lock(int *my_lock){
    asm ("movl $1, %%eax;"
        "xchg %%eax, %0;"
        :"=&r"(*my_lock) //y is output operand, note the & constraint modifier.
        :"r"(*my_lock)   //x is input operand 
        :"%eax"); //%eax is clobbered register     
}


void unlock(int *my_lock){
    asm ("movl $0, %%eax;"
        "xchg %%eax, %0;"
        :"=&r"(*my_lock) //y is output operand, note the & constraint modifier.
        :"r"(*my_lock)   //x is input operand 
        :"%eax"); //%eax is clobbered register     

}

void *worker(void *section_crit_count){
    int *count = (int *)section_crit_count; //come dans philosophe
    for (int i = 0; i < *count; i++)
    {
        lock(&lock_int);
        //if (lock_int == 0)
        //{
        //    printf("fuckit_locked\n");
        //}
        
        //printf("Consuming: %d\n", i);
        for (int j = 0; j < 10000; j++)
        {
            /* code */
        }
        unlock(&lock_int);
        //if (lock_int != 0)
        //{
        //    printf("fuckit_unlocked: %d\n", lock_int);
        //}

    }
    
}

int main(int argc, char *argv[]){
    nb_threads = atoi(argv[1]);

    int *section_crit_count = (int *)malloc(sizeof(int));
    *section_crit_count = 6400/nb_threads;
    //printf("section_critique_count: %d \n", *section_crit_count);

    int *section_crit_count_end = (int *)malloc(sizeof(int));
    *section_crit_count_end = *section_crit_count + 6400 - (*section_crit_count * nb_threads); //comme dans prodcons
    //printf("section_critique_count_end: %d \n", *section_crit_count_end);

    pthread_t threads[nb_threads];
    for (int i = 0; i < nb_threads; i++)
    {
        if (i == nb_threads-1)
        {
            pthread_create(&threads[i], NULL, &worker, (void *) section_crit_count_end);
            //printf("Created thread end: %d\n", i);
        }else
        {
            pthread_create(&threads[i], NULL, &worker, (void *) section_crit_count);
            //printf("Created thread: %d\n", i);
        }
    
    }
    for (int k = 0; k < nb_threads; k++)
    {
        pthread_join(threads[k], NULL); //devrait check si join est bien fait 
    }
    return 0;
}