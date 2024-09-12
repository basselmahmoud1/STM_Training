
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"HMM.h"
/**/
#define NUM_ALLOCS 10000
#define MAX_SIZE 10240
#define MAX_ITERATIONS 1000000

void random_alloc_free_test() {
    srand((unsigned int)time(NULL));

    void* pointers[NUM_ALLOCS] = {NULL};
    int i ;
    for (i = 0; i < MAX_ITERATIONS; ++i) {
        int index = rand() % NUM_ALLOCS;
        if (pointers[index] == NULL) {
            // Allocate memory
            size_t size = (size_t)(rand() % MAX_SIZE) + 1;
            pointers[index] = HmmAlloc(size);

            if (pointers[index] != NULL) {
                printf("Allocated memory of size %zu at address %p\n", size, pointers[index]);
            } if ((size_t)(pointers[index]) % 8 != 0) {
                fprintf(stderr, "Allocation failed for size %zu\n", size);
                exit(0);
            }

        } else {
            // Free memory
            printf("Freeing memory at address %p\n", pointers[index]);
            HmmFree(pointers[index]);
            pointers[index] = NULL;
        }
    }

    // Free remaining allocated memory
    for ( i = 0; i < NUM_ALLOCS; ++i) {
        if (pointers[i] != NULL) {
            printf("Freeing remaining memory at address %p\n", pointers[i]);
            HmmFree(pointers[i]);
            pointers[i] = NULL;
        }
    }
}

int main() {
    printf("Starting random allocation and deallocation test...\n");
    random_alloc_free_test();
    printf("Test complete.\n");
    return 0;
}



/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2023.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/


/*
// Listing 7-1

//#define _BSD_SOURCE
//#include "tlpi_hdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "HMM.h"

#define MAX_ALLOCS 1000000

#define getInt(x, ...) atoi(x)

extern char end, edata, etext;

#if 1
// Enable if you want to replace libc malloc/free 
void * malloc (size_t size) {
    return HmmAlloc(size);
}

void free(void *ptr) {
    HmmFree(ptr);
}

void *calloc(size_t nmemb,size_t size) {
    void* ptr = HmmAlloc(nmemb*size);
    memset(ptr,0,nmemb*size);
    return ptr ;
}

void *realloc(void *ptr ,size_t size ) {
    if(ptr == NULL)
        return HmmAlloc(size);
    if(size == 0 ) {
        HmmFree(ptr);
        return NULL ;
    }
    node_mod* req = (node_mod*)((int*) ptr -2)  ;

    if(size > req->size) {//allocate new memory
        node_mod* sercher = head ;
        while ( sercher != NULL && sercher < req ) {
            sercher = sercher->ptrNext ;
        }
        node_mod* carrier = sercher ;
        if(sercher!=NULL && sercher == (node_mod*)((char*)req +req->size+sizeof(node_mod)) ) { // checking if there is adjacent node
            if( sercher->size+ sizeof(node_mod)+ req->size > size) { // check size if it can carry the new size nedded to be allocated
                req ->size = size ;
                // remove the node
                deleteNode(sercher);
                return ptr;
            }
        }
        else {  // search for another node that have that size free
            //search for the free location
            sercher=head;
            if(sercher->size > size) {
                //delete node
                deleteNode(sercher);
                // copy data from the req location to the new location
                memmove((char*)sercher,(char*)req,req->size);
                if(carrier!=NULL)
                    req->ptrPrev = carrier->ptrPrev ;
                insert_node_mod(req);
                // modify the size of the new location
                sercher->size = size ;
                //return the new location
                int * newptr = (int*)sercher ;
                newptr += 2 ;
                return (void*)newptr ;
            }
            else {
                sercher=sercher->ptrNext;
            }


        }


    }

    else if (size < req->size) { //free memory
        int remaining_size = req->size - size;
        req->size=size;
        node_mod * newnode = (node_mod*) ((char*)req + size + sizeof(node_mod));
        newnode->size = remaining_size ;
        node_mod* sercher = head ;
        while ( sercher < newnode && sercher != NULL ) {
            sercher = sercher->ptrNext ;
        }
        if (sercher != NULL) {
            sercher = sercher->ptrPrev;
        }
        newnode->ptrPrev = sercher;
        insert_node_mod(newnode);
        return ptr;

    }

    return ptr ; //size is equal to req size


}
#endif

int
main(int argc, char *argv[])
{
	//sleep(5);
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;
   printf("etext = %p, edata=%p, end=%p, initial program break=%p &sbrk=%p \n", &etext, &edata, &end,program_break,(char*)sbrk(0));

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
        exit(1);
    }

    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");
    if (numAllocs > MAX_ALLOCS) {
        printf("num-allocs > %d\n", MAX_ALLOCS);
        exit(1);
    }

    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    freeMin =  (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    freeMax =  (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : numAllocs;

    if (freeMax > numAllocs) {
       // printf("free-max > num-allocs\n");
        exit(1);
    }

    printf("Initial sbrk:          %10p& prog : %10p\n ", sbrk(0),program_break);

    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for (j = 0; j < numAllocs; j++) {
        ptr[j] = HmmAlloc(blockSize);
        if (ptr[j] == NULL) {
          printf("malloc returned null\n");
            exit(1);
        }
    }

     printf("Program break is now:           %10p\n", sbrk(0));

    printf("Freeing blocks from %d to %d in steps of %d\n",freeMin, freeMax, freeStep);
    for (j = freeMin - 1; j < freeMax; j += freeStep)
        HmmFree(ptr[j]);

    printf("After free(),sbrk is: %10p& prog : %10p\n ", sbrk(0),program_break);
   while(1);

    exit(EXIT_SUCCESS);
    }
/*
//#include "HMM.h"
int main (void)
{
	int i =0 ;
	char*ptr= HmmAlloc(900);
	char * carry = ptr ;
	for(i=0 ; i < 900 ; i++ )
	{

		*carry = i ;
		printf("memory address : %p ,value in it : %d \n",carry,*carry);
		carry++;
	}
	
	HmmFree(ptr);

}
*/

