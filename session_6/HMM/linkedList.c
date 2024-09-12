//
// Created by Bassel Mahmoud on 12/8/2024.
//

#include "linkedList.h"

int counter = 1 ;



void deleteNode(node_mod* req_delete)
{
    if(req_delete==NULL || head == (node_mod*)program_break) {
        return;
    }

    node_mod* next =req_delete->ptrNext;
    node_mod* before =req_delete->ptrPrev;

    if(req_delete == (node_mod*)base) {
        if(next!=NULL) {
             next->ptrPrev = (node_mod*)base;
             head = next ;
        }
        else {
            head = (node_mod*)program_break;
        }
        req_delete->ptrNext = NULL;
        req_delete->ptrPrev = NULL;
        return;
    }

    if(req_delete == head ) {// checking if it is the first node
        if(next==(node_mod*)program_break) {
            head = (node_mod*) program_break;
        }
        else {
            next->ptrPrev = (node_mod*)base;
            head = next ;
        }

        req_delete->ptrNext=NULL;
        req_delete->ptrPrev=NULL;
        return;

    }

    if(req_delete->ptrNext == (node_mod*)program_break ) {
        before->ptrNext = (node_mod*)program_break;
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

void insert_node_mod(node_mod* insert ) //node must contain its prev pointer when given to be inserted at middle automatically
{        
	if ( head == NULL) {
	    head = insert;
	    insert->ptrNext = (node_mod*)program_break;
	    insert->ptrPrev = (node_mod*)base;

	}
	else if (insert < head) {
	    insert->ptrNext = head;
	    insert->ptrPrev = head->ptrPrev;
	    head->ptrPrev = insert;
	    head = insert;

	}

	else {

	node_mod* sercher = head;
	while (sercher->ptrNext != (node_mod*)program_break && sercher->ptrNext < insert) {
	sercher = sercher->ptrNext;
	}

	insert->ptrNext = sercher->ptrNext;
	if (sercher->ptrNext != (node_mod*)program_break) {
	sercher->ptrNext->ptrPrev = insert;
	}
	insert->ptrPrev = sercher;
	sercher->ptrNext = insert;

	}
	node_mod* examin = head ;
	int flag_head =0 ;
	while (examin->ptrNext != (node_mod*)program_break) {
	examin = examin->ptrNext;
	}

	if( (char*)examin < (program_break-PAGE_SIZE ) ) {
	int remaining_space = (int)(program_break - (char*)examin) ;
	int units =remaining_space/PAGE_SIZE;
	if(head == (node_mod*)program_break)
	    flag_head=1;
	if(units>1) {
	    units-- ;
	    program_break = program_break-units*PAGE_SIZE;
	    examin->ptrNext =(node_mod*)program_break;
	    if(flag_head == 1)
		head = (node_mod*)program_break;

	    remaining_space = (int)(program_break - (char*)examin);
	    examin->size=remaining_space;
	    return;
	}
	else {
	    return;
	}
}
}

// search for data
