//
// Created by Bassel Mahmoud on 12/8/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "HMM.h"

#define Size_of_heap 1073741824

typedef struct node_mod {
    size_t size ;
    struct node_mod * ptrNext ;
    struct node_mod * ptrPrev ;
}node_mod;



/*
extern node_mod* head   ;
extern char* program_break;
extern char*  base ;
*/
//void fillDataNode (node_mod * req_filled);
void deleteNode(node_mod* req_delete);
void insert_node_mod(node_mod* insert);
//extern char HeapMemory [Size_of_heap];


#endif //LINKEDLIST_H
