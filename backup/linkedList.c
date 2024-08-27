//
// Created by Bassel Mahmoud on 12/8/2024.
//

#include "linkedList.h"


int counter = 1 ;
long long debuger = 0 ;

void deleteNode(node_mod* req_delete)
{
    if(req_delete==NULL || head == NULL) {
        return;
    }

    node_mod* next =req_delete->ptrNext;
    node_mod* before =req_delete->ptrPrev;

    if(req_delete == (node_mod*)base) {
        if(next != NULL) { //(next != NULL)
             next->ptrPrev = (node_mod*)base;
             head = next ;
        }
        else {      // there is no free node 
            head = NULL;
        }
        req_delete->ptrNext = NULL;
        req_delete->ptrPrev = NULL;
        return;
    }

    if(req_delete == head ) {// checking if it is the first node
        if(next==NULL) {
            head = NULL;
        }
        else {
            next->ptrPrev = (node_mod*)base;
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
	if ( head == NULL) {
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
 //   3472328296227680273
    else {

	    node_mod* sercher = head;
	    while (sercher->ptrNext != NULL && sercher->ptrNext < insert) {
		sercher = sercher->ptrNext;
	    }

	    insert->ptrNext = sercher->ptrNext;
	    if (sercher->ptrNext != NULL) {  // !=
		sercher->ptrNext->ptrPrev = insert;
	    }
	    insert->ptrPrev = sercher;
        
	    sercher->ptrNext = insert;

    }
    node_mod* examin = head ;
    int flag_head =0 ;
    while (examin->ptrNext != NULL) {
        examin = examin->ptrNext;
    }

    if( (char*)examin < (char*)((char*)program_break ) ) {
        int remaining_space = (int)((char*)program_break - (char*)examin-sizeof(node_mod)) ;
        
        int units =remaining_space/(PAGE_SIZE*2);
        // if(head == NULL)
        //     flag_head=1;
        if(units>4) {
            units-- ;
            program_break_change(-units*PAGE_SIZE);
            examin->ptrNext =NULL; //update with the new program_break
            // if(flag_head == 1)
            //     head = (node_mod*)program_break;

            remaining_space = (int)((char*)program_break - (char*)examin- sizeof(node_mod));
            examin->size=remaining_space;
            return;
        }
        else {
            return;
        }
    }
}

// search for data
