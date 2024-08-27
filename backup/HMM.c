
#include "HMM.h"



#ifdef SARR
char HeapMemory [Size_of_heap];
char* program_break = &HeapMemory[0];
char*  base = &HeapMemory[0];
#endif

#ifdef HEAP
char* program_break = NULL;
char*  base = NULL ;
int flag_init=0;
#endif

int debug =0; 
node_mod* head = NULL ;
const size_t sizenode = alignsize(sizeof(node_mod));

void* HmmAlloc (size_t size)
{

    if(size == 0)
        size = sizenode+10;
	if(debug == 0 )
	{
		//sleep(20);
		debug=1 ;
	}
    size = alignsize(size);
	
	if(size == 0 )
		return NULL ;
		
	
		
	#ifdef HEAP
	//initialize the program break and base
	if(flag_init==0)
	{	
		base = program_break_change(0) ;
		program_break= program_break_change(PAGE_SIZE*4);
		if(program_break == (char*)-1)
		{
			perror("sbrk");
			return NULL;
		}
        head = (node_mod*) base; 
        head->size= (int)(program_break - base -sizenode) ; 
        head->ptrNext = NULL ;
        head->ptrPrev = NULL ;

		flag_init = 1;
	}
	#endif
  //  (node_mod*) HeapMemory
    // if(head == NULL) {
    //     node_mod* initial_node = (node_mod*)base;
    //     insert_node_mod(initial_node);
    // }

    node_mod* sercher = head ;
    // list is empty
    //check if there is an accepted free node in the middle
    while (sercher->ptrNext != NULL) {   // !=
        if(sercher->size >= size+sizenode) {
        	// bos hena mmkn tshof 3lshan my3odsh y3mel nodes free so8ayara awy 
            if(sercher->size-size>sizenode) // lazem el makan el ba2i ykafi enna n3mel node gededa
            {
                node_mod * split_mem = (node_mod*)((char*)sercher+size+sizenode);
            
                split_mem->ptrPrev = sercher->ptrPrev;
                if(sercher->size - size - sizenode <= 0)
                {  
                    perror("size isnt enough to split");    
                    return NULL;
                }
                split_mem->size = sercher->size - size - sizenode;
                
                insert_node_mod(split_mem);
                sercher->size = size ;
                sercher->ptrNext = split_mem;
            }
            node_mod * ptr = sercher ;
            ptr +=1 ;
            deleteNode(sercher);
            return (void*)ptr ;
        }
        sercher = sercher->ptrNext ;
    }

// check if the avaliablie size of the last node is big enough for the new size nedded to be allocated
    if (size >= (int)((char*)program_break-(char*)sercher-sizenode)) {
        int req_space = size - ((int)((char*)program_break-(char*)sercher));
        int units = req_space/PAGE_SIZE ;
        units += 2 ;
         
        program_break_change(PAGE_SIZE*(units));
        
        sercher->ptrNext = NULL ; // the new program break value
        node_mod * split_mem = (node_mod*)((char*)sercher+size+sizenode); //edited
        split_mem->ptrPrev = sercher->ptrPrev;
        split_mem->size= (int)((char*)program_break-(char*)split_mem) - sizenode ;
        insert_node_mod(split_mem);
        
        
        sercher->size = size ;
       // sercher->ptrNext = split_mem;
        node_mod * ptr = sercher ;
        ptr +=1 ;
        deleteNode(sercher);
        return (void*)ptr ;

    }
    /////////////////////////////////////////ANA w2eft heana
    else if (sercher->ptrNext == NULL   ) {
  
          //  printf("hello");
          //	char*debug = sbrk(0);//for debugging
          
            node_mod* split_mem = (node_mod*)((char*)sercher+size+sizenode); //edited
            if( program_break - (char*)split_mem <= sizenode)
            {
               // write(1,"entered inc space in the second time\n",38);
            	int req_space = ((int)((char*)split_mem-(char*)program_break));
            	int units = req_space/PAGE_SIZE ;
                units += 2 ;
                program_break_change(PAGE_SIZE*(units));
                sercher->ptrNext = NULL;
	        }
	    //char* debug2 = sbrk(0);
            //printf("hi");

            split_mem->ptrPrev = sercher;
            split_mem->size = (char*)program_break - (char*)split_mem - sizeof(node_mod*);

            insert_node_mod(split_mem);

            sercher->size = size ;
            node_mod * ptr = sercher ;
            ptr +=1 ;
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
    node_mod* req = (node_mod*) ptr -1  ;
    node_mod* sercher = head ;

    while ( sercher < req && sercher != NULL ) { //( sercher < req && sercher != NULL )
        if(sercher->ptrNext == NULL)
        {
            break ;    
        }
        sercher = sercher->ptrNext ;
    }

    if (sercher != NULL) { //(sercher != NULL)
        sercher = sercher->ptrPrev;
    }
    

    req->ptrPrev = sercher;

    insert_node_mod(req);

    sercher = head;
    node_mod* next = sercher->ptrNext; 
    while (sercher != NULL && sercher->ptrNext != NULL ) {
        // Check if the current block and the next block are adjacent in memory
        if ((char*)next == (char*)sercher + sercher->size + sizenode) {
            // Merge the current block with the next block
            sercher->size += next->size + sizenode;
            sercher->ptrNext = next->ptrNext;

            // Update the next block's prev pointer, if it's not the end of the list
            if (next->ptrNext != NULL) {
                next->ptrNext->ptrPrev = sercher;
            }
        } 
        else 
        {
            // Move to the next block in the list
            sercher = sercher->ptrNext;
            if(sercher->ptrNext != NULL)
                next = sercher->ptrNext;
            else
                break;
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

void* realloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        // If pointer is NULL, behave like malloc
        return HmmAlloc(size);
    }

    if (size == 0) {
        // If size is 0, free the memory and return NULL
        HmmFree(ptr);
        return NULL;
    }

    // Get the node structure from the pointer
    node_mod* req = (node_mod*)((char*)ptr - sizenode);

    // Case 1: Need to allocate more memory
    if (size > req->size) {
        node_mod* searcher = head;

        // Find the node that comes after the current block
        while (searcher != NULL && searcher < req) {
            searcher = searcher->ptrNext;
        }

        // Check if the next node is adjacent and can be merged
        if (searcher != NULL && searcher == (node_mod*)((char*)req + req->size + sizenode)) {
            if (searcher->size + req->size + sizenode >= size) {
                // Resize by merging with the next block
                if (searcher->size + req->size + sizenode > size + sizenode) {
                    // If there is enough memory for the node to be created, split memory
                   node_mod* split_mem = (node_mod*)((char*)req + size + sizenode);
                    split_mem->size = searcher->size + req->size - size;
                    split_mem->ptrPrev = req;
                    insert_node_mod(split_mem);
                } else {
                    // Increase the requested size by the remaining size
                    size = searcher->size + req->size;
                }

                req->size = size;

                // Remove the next node from the free list
                deleteNode(searcher);
                return (void*)ptr;
            }
        } else {
            // Search for another suitable free block
            searcher = head;
            while (searcher != NULL) {
                if (searcher->size >= size) {
                    if (searcher->size > size + sizenode) {
                        // Split and create a new node
                        node_mod* split_mem = (node_mod*)((char*)searcher + size + sizenode);
                        split_mem->size = searcher->size - size - sizenode;
                        split_mem->ptrPrev = searcher;
                        insert_node_mod(split_mem);
                        searcher->size = size;
                    } else {
                        // Increase the requested size by the remaining size
                        size = searcher->size;
                        searcher->size = size;
                    }

                    // Move data to the new block
                    memmove((char*)searcher + sizenode, ptr, req->size);

                    // Remove the old block
                    HmmFree(ptr);

                    // Return the new pointer
                    return (void*)((char*)searcher + sizenode);
                }
                searcher = searcher->ptrNext;
            }
        }

        // If no suitable block found, allocate a new block
        void* new_ptr = HmmAlloc(size);
        if (new_ptr != NULL) {
            // Copy data to the new block
            memmove(new_ptr, ptr, req->size);

            // Free the old block
            HmmFree(ptr);
        }
        return new_ptr;

    } else if (size < req->size) {
        // Case 2: Need to reduce the size
        size_t remaining_size = req->size - size;

        if (remaining_size > sizenode) {
            // Create a new block for the remaining memory
            node_mod* new_node = (node_mod*)((char*)req + size + sizenode);
            new_node->size = remaining_size - sizenode;
            insert_node_mod(new_node);
            req->size = size;
        }

        return ptr;
    }

    return ptr; // If size is the same, just return the original pointer
}


#endif



void* program_break_change(size_t increment) {
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

