
#include "HMM.h"

extern char end ;

#ifdef SARR
char HeapMemory [Size_of_heap];
char* program_break = &HeapMemory[0];
char*  base = &HeapMemory[0];
#endif

#ifdef HEAP
char*program_break = NULL;
char*  base = NULL ;
int flag_init=0;
#endif


node_mod* head = NULL ;


void* HmmAlloc (size_t size)
{

	#ifdef HEAP
	//initialize the program break and base
	if(flag_init==0)
	{
		program_break=(char*)program_break_change(0);
		if(program_break == (char*)-1)
		{
			perror("sbrk");
			return NULL;
		}
		base = &end ;
		flag_init = 1;
	}
	#endif
  //  (node_mod*) HeapMemory
    if(head == NULL) {
        node_mod* initial_node = (node_mod*)base;
        insert_node_mod(initial_node);
    }

    node_mod* sercher = head ;
    // list is empty
    while (sercher->ptrNext != (node_mod*)program_break_change(0)) {
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


    if (size > (int)((char*)program_break_change(0)-(char*)sercher)) {
        int req_space = size - ((int)((char*)program_break_change(0)-(char*)sercher));
        int units = req_space/PAGE_SIZE ;
        units += 2 ;
         
        program_break_change(PAGE_SIZE*(units));
        sercher->ptrNext = (node_mod*)program_break_change(0) ;
        node_mod * split_mem = (node_mod*)((char*)sercher+size+sizeof(node_mod)); //edited
        split_mem->ptrPrev = sercher->ptrPrev;
        split_mem->size= (int)((char*)program_break_change(0)-(char*)split_mem) - sizeof(node_mod*) ;
        insert_node_mod(split_mem);
        
        
        sercher->size = size ;
       // sercher->ptrNext = split_mem;
        int * ptr = (int*)sercher ;
        ptr += 2 ;
        deleteNode(sercher);
        return (void*)ptr ;

    }
    else if (sercher->ptrNext == (node_mod*)program_break_change(0)   ) {
  
            node_mod * split_mem = (node_mod*)((char*)sercher+size+sizeof(node_mod)); //edited
            
            split_mem->size = (char*)program_break_change(0) - (char*)split_mem - sizeof(node_mod*);
            
            //split_mem->ptrPrev = sercher->ptrPrev;
            split_mem->ptrPrev = sercher;
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
    // *((int*)ptr)=0;
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
    while (sercher != (node_mod*)program_break_change(0) && sercher->ptrNext != (node_mod*)program_break_change(0)) {
        node_mod* next = sercher->ptrNext;

        // Check if the current block and the next block are adjacent in memory
        if ((char*)next == (char*)sercher + sercher->size + sizeof(node_mod)) {
            // Merge the current block with the next block
            sercher->size += next->size + sizeof(node_mod);
            sercher->ptrNext = next->ptrNext;

            // Update the next block's prev pointer, if it's not the end of the list
            if (next->ptrNext != (node_mod*)program_break_change(0)) {
                next->ptrNext->ptrPrev = sercher;
            }
        } else {
            // Move to the next block in the list
            sercher = sercher->ptrNext;
        }
    }

}

#ifdef replacelibc
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



void* program_break_change(int increment) {
#ifdef SARR
    // For static array, just return the updated pointer
    return program_break += increment;
#endif

#ifdef HEAP
    // For heap, use sbrk to increase the heap size
    char* ptr = (char*)sbrk(increment);
    if (ptr == (char*)-1) {
        perror( "Error: sbrk failed");
        return NULL;
    }
    program_break = (char*)sbrk(0) ;
    return program_break;
#endif
}

