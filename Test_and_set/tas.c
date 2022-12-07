#include "../Headers/tas.h"

int tas(int *my_lock, int update){
    int status;
    asm ("movl %2, %%eax;"
        "xchg %%eax, %0;"
        "movl %%eax, %1"
        :"=&r"(*my_lock),
        "=&m" (status)
        :"r"(update)   //x is input operand 
        :"%eax"); //%eax is clobbered register
        return status;     

}


void lock(int *my_lock){
    while (tas(my_lock, 1))
    {
        /* code */
    }
    
}


void unlock(int *my_lock){
    tas(my_lock, 0);
}