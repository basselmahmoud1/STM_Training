#include "myfdisk.h"

int main (int argc, char** argv ) {
    //read the MPR
    if(argc == 1)
    {
        printf("Please enter file\n");
        return 0;
    }
    char buf[512];
    int fd = open (argv[1],O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return 0 ;
    }
    read (fd,buf,512);
    

    // casting a pointer to read all of the partition table 
    partition_entry* table_ptr = (partition_entry*) &buf [Entry_index_begin] ;
    partition_entry* extended_ptr = NULL ;

    int i , flag_Ex = 0;
    for(i = 1 ; i <= 4 ; i++)
    {
        if(table_ptr->type == 0xEE )
        {
            //protective MBR is detected
            print_table(table_ptr,GPT,i,fd,argv);
        }
        else if(table_ptr->type != 0)
        {
            //MBR 
            print_table(table_ptr,normalMBR,i,fd,argv);
           // flag_Ex = 0 ;
        }
        if(table_ptr->type == 0x05) 
        {
            flag_Ex = i ;
            extended_ptr = table_ptr; 
            
        }
    
        table_ptr ++ ;

    }
    if(extended_ptr!=NULL)
    {
        // print the External partitions
        //get the correct extended table

        print_table(extended_ptr,Extended,flag_Ex,fd,argv);
    }

}

