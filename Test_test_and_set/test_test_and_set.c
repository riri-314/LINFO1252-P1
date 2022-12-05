
// pour le atoi
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int nb_threads = 0;
int lock_int = 0;

int lock(int *my_lock){ 
    int lock_status;
    asm ("movl $1, %%eax;"
        "xchg %%eax, %0;"
        "movl %%eax, %1" //put original status of my_lock into lock status. If lock_status = 0, my_lock passed from 0 to 1 else my_lock passed from 1 to 1
        :"=&r"(*my_lock),
        "=&m" (lock_status) //
        :"r"(*my_lock)   //x is input operand 
        :"%eax"); //%eax is clobbered register
        return lock_status;     
}

void unlock(int *my_lock){
    asm ("movl $0, %%eax;"
        "xchg %%eax, %0;"
        :"=&r"(*my_lock) //y is output operand, note the & constraint modifier.
        :"r"(*my_lock)   //x is input operand 
        :"%eax"); //%eax is clobbered register     

}

void lock_ttas(int *my_lock){
    while (lock(my_lock)) //lock output a int. If int = 1 my_lock is locked [wait], elif int = 0 my_lock was free and as been locked [succes]
    {
        while (*my_lock) //checking status of int *my_lock. If *my_lock = 1 lock can be acquired [succes] else loop [wait] 
        {
            /* code */
        }
        
    }
    
}

void *worker(void *section_crit_count){
    int *count = (int *)section_crit_count; //come dans philosophe
    for (int i = 0; i < *count; i++)
    {
        lock_ttas(&lock_int);
        //if (lock_int == 0)
        //{
        //    printf("fuckit_locked\n");
        //}
        //
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

//int main(){
//    //printf("my_lock_unlocked: %d\n", lock_int);
//
//    return 0;
//}