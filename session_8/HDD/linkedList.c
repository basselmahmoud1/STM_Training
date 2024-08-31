//
// Created by Bassel Mahmoud on 12/8/2024.
//

#include "linkedList.h"

int counter = 1 ;
node* head = NULL ;


// void fillDataNode (node * req_filled) {

//     if(req_filled == NULL ) {
//         printf("NULL Pointer ALERT");
//         return;
//     }
//     printf("plese enter id followed by name followed by rank \n");
//     scanf("%d%s%d",req_filled ->data.id,req_filled ->data.name,req_filled ->data.rank);
// }

void addNode (void) {

    node * LASTnode = NULL ;  // carrier to find the last node to enter new node after it
    node * Newnode =  NULL ;  //

    // check if the list is empty
    if ( (head->ptrNext) == NULL) {
        Newnode = (node *) malloc(sizeof(node));
        if (Newnode == NULL) {
            printf("malloc failed");
            return;
        }
        head = Newnode;
       // fillDataNode(Newnode);
    }
    else
    {
        LASTnode = head;
        LASTnode->ptrNext =  Newnode;
        while (LASTnode->ptrNext != NULL) {
            LASTnode =  LASTnode->ptrNext;
        }
        // allocate memory for the new node
        Newnode = (node *) malloc(sizeof(node));
        if (Newnode == NULL) {
            printf("malloc failed");
            return;
        }
      //  fillDataNode(Newnode);
    }
    counter++;
    Newnode->ptrNext = NULL ;
}

void deleteNode(int location) {

    if (location <= 0 || location >= counter + 1) {
        printf("invalied loaction ");
        return;
    }
    node *prev = head;
    node* req_delete = head ;
    int internal_counter = 1;


    if (location == 1) {
        head = req_delete->ptrNext ;
        free(req_delete);
        req_delete==NULL;
        counter--;
        return;
    }

    while (internal_counter != location - 1) {
        prev = prev->ptrNext;
        internal_counter++;
    }


    req_delete=prev->ptrNext;
    prev->ptrNext = req_delete->ptrNext;
    free(req_delete);
    req_delete==NULL;
    counter--;

    }

void insert_node(int location) // location index start from 1 //
{
    node *insert = (node *) malloc(sizeof(node));
    if (insert == NULL) {
        printf("malloc failed");
        return;
    }
    //fillDataNode(insert);

    node *prev = head;
    int internal_counter = 1;
    if (location <= 0 || location > counter + 1) {
        printf("invalied loaction ");
        return;
    }


    if (location == 1) {
        insert->ptrNext = head;
        head = insert;
        counter++;
        return;
    }
    while (internal_counter != location - 1) {
        prev = prev->ptrNext;
        internal_counter++;
    }

    insert->ptrNext = prev->ptrNext;
    prev->ptrNext = insert;
    counter++;
}
