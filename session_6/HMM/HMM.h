#ifndef HMM_H
#define HMM_H

#include "linkedList.h"

#define Size_of_heap 1073741824   // 1 GB of heap
#define PAGE_SIZE  4096



void* HmmAlloc (size_t size);


void HmmFree (void * ptr);

#endif // HMM_H
