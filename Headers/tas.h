#ifndef TAS_H
#define TAS_H

int tas(int *my_lock, int update);

void lock(int *my_lock);

void unlock(int *my_lock);

#endif