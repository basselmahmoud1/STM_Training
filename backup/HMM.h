#ifndef HMM_H
#define HMM_H


#include <string.h>
#include <unistd.h>
#include "linkedList.h"

#define Size_of_heap 1073741824
#define PAGE_SIZE  4096
#define replacelibc // NOreplace or replacelibc
#define HEAP    // HEAP or SARR

void* HmmAlloc (size_t size);

void HmmFree (void * ptr);

void* program_break_change(size_t increment) ;

#define alignsize(x)  ((x)+7)&~7


#ifdef SARR
extern char HeapMemory [];
extern char* program_break ;
extern char*  base ;
extern struct node_mod* head;
#endif

#ifdef HEAP
extern char* program_break;
extern char*  base ;
extern int flag_init;
extern struct node_mod* head;
extern char end ;
extern const size_t sizenode;


#endif


#ifdef replacelibc
void * malloc (size_t size);
void free(void *ptr);
void *calloc(size_t nmemb,size_t size);
void *realloc(void *ptr ,size_t size );
#endif

#endif // HMM_H
