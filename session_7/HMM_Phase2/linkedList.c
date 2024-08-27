//
// Created by Bassel Mahmoud on 12/8/2024.
//

#include "linkedList.h"


size_t counter = 1 ;
long long debuger = 0 ;

void deleteNode(node_mod* req_delete)
{
    if(req_delete==NULL || head == NULL) {
        return;
    }

    node_mod* next =req_delete->ptrNext;
    node_mod* before =req_delete->ptrPrev;

    // if(req_delete == (node_mod*)base) {
    //     if(next != NULL) { //(next != NULL)
    //          next->ptrPrev = (node_mod*)base;
    //          head = next ;
    //     }
    //     else {      // there is no free node 
    //         head = NULL;
    //     }
    //     req_delete->ptrNext = NULL;
    //     req_delete->ptrPrev = NULL;
    //     return;
    // }

    if(req_delete == head ) {// checking if it is the first node
        if(next==NULL) {
            head = NULL;
        }
        else {
            next->ptrPrev = req_delete;
            head = next ;
        }

        req_delete->ptrNext=NULL;
        req_delete->ptrPrev=NULL;
        return;

    }

    if(req_delete->ptrNext == NULL ) {
        before->ptrNext = NULL;
        req_delete->ptrNext=NULL;
        req_delete->ptrPrev=NULL;
        return;
    }
    before->ptrNext=next;
    next->ptrPrev=before;
    req_delete->ptrNext=NULL;
    req_delete->ptrPrev=NULL;
    return;

   
}

void insert_node_mod(node_mod* insert ) 
{
	  debuger++ ;        
	if ( head == NULL) { // list is empty no free nodes
	    head = insert;
	    insert->ptrNext = NULL;
	    insert->ptrPrev = NULL;
	}
	else if (insert < head) {
	    insert->ptrNext = head;
	    insert->ptrPrev = NULL;
	    head->ptrPrev = insert;
	    head = insert;

	}
    else {

	    node_mod* sercher = head;
	    while (sercher->ptrNext != NULL && sercher->ptrNext < insert) {
		sercher = sercher->ptrNext;
	    }
        // searcher is the node before the req to insert 

	    insert->ptrNext = sercher->ptrNext;
	    if (sercher->ptrNext != NULL) {  // !=
		sercher->ptrNext->ptrPrev = insert;
	    }
	    insert->ptrPrev = sercher;
        
	    sercher->ptrNext = insert;

    }
    
}

// search for data
