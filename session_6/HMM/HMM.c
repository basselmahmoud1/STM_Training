
#include "HMM.h"
char HeapMemory [Size_of_heap];

char* program_break = &HeapMemory[0];
char*  base = &HeapMemory[0];
node_mod* head = NULL ;



void* HmmAlloc (size_t size)
{
  //  (node_mod*) HeapMemory
    if(head == NULL) {
        node_mod* initial_node = (node_mod*)base;
        insert_node_mod(initial_node);
    }

    node_mod* sercher = head ;
    // list is empty
    while (sercher->ptrNext != (node_mod*)program_break) {
        if(sercher->size >= size+sizeof(node_mod)) {
            node_mod * split_mem = (node_mod*)((char*)sercher+size+sizeof(node_mod));
            split_mem->ptrPrev = sercher->ptrPrev;
            split_mem->size = sercher->size - size - sizeof(node_mod);
            insert_node_mod(split_mem);
            sercher->size = size ;
            sercher->ptrNext = split_mem;
            int * ptr = (int*)sercher ;
            ptr +=2 ;
            deleteNode(sercher);
            return (void*)ptr ;
        }
        sercher = sercher->ptrNext ;
    }


    if (size > (int)(program_break-(char*)sercher)) {
        int req_space = size - ((int)(program_break-(char*)sercher));
        int units = req_space/PAGE_SIZE ;
        units += 2 ;
        program_break += PAGE_SIZE*(units) ;
        sercher->ptrNext = (node_mod*)program_break ;
        node_mod * split_mem = (node_mod*)((char*)sercher+size+sizeof(node_mod)); //edited
        split_mem->ptrPrev = sercher->ptrPrev;
        split_mem->size= (int)(program_break-(char*)split_mem) - sizeof(node_mod*) ;
        insert_node_mod(split_mem);
        sercher->size = size ;
       // sercher->ptrNext = split_mem;
        int * ptr = (int*)sercher ;
        ptr += 2 ;
        deleteNode(sercher);
        return (void*)ptr ;

    }
    else if (sercher->ptrNext == (node_mod*)program_break && (program_break+sercher->size)< &HeapMemory[Size_of_heap-1] )
        {
            node_mod * split_mem = (node_mod*)((char*)sercher+size+sizeof(node_mod)); //edited
            split_mem->ptrPrev = sercher->ptrPrev;
            split_mem->size = program_break - (char*)split_mem - sizeof(node_mod*);
            insert_node_mod(split_mem);

            sercher->size = size ;
            int * ptr = (int*)sercher ;
            ptr += 2 ;
            deleteNode(sercher);
            return (void*)ptr ;
    }

    else
        return NULL ;
}



void HmmFree (void * ptr ) {
    // iterate through nodes and check the adrress if it lies between 2 nodes of not

    if(ptr == NULL)
        return;

    node_mod* req = (node_mod*)((int*) ptr -2)  ;
    node_mod* sercher = head ;

    while ( sercher < req && sercher != NULL ) {
        sercher = sercher->ptrNext ;
    }

    if (sercher != NULL) {
        sercher = sercher->ptrPrev;
    }

    req->ptrPrev = sercher;

    insert_node_mod(req);

    sercher = head;
    while (sercher != (node_mod*)program_break && sercher->ptrNext != (node_mod*)program_break) {
        node_mod* next = sercher->ptrNext;

        
        if ((char*)next == (char*)sercher + sercher->size + sizeof(node_mod)) {
            sercher->size += next->size + sizeof(node_mod);
            sercher->ptrNext = next->ptrNext;

        if (next->ptrNext != (node_mod*)program_break) {
                next->ptrNext->ptrPrev = sercher;
            }
        } else {
            sercher = sercher->ptrNext;
        }
    }

}



