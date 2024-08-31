//
// Created by Bassel Mahmoud on 12/8/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "myfdisk.h"



typedef struct node {
    struct node * ptrNext ;
}node;

typedef enum {
    NULL_ptr,
    EMPTY_list,
    Error_heap,
}errorState;

extern node* head  ;

//void fillDataNode (node * req_filled);
void addNode (void) ;
void deleteNode(int  location );
void insert_node (int  location );


#endif //LINKEDLIST_H
