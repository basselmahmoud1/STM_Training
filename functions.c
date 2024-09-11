#include "functions.h"

uint8_t f_l , f_a , f_t , f_u, f_c, f_i, f_f, f_d, f_1,f_noopt,f_error;
// index of the 
uint8_t argv_index_beg1 = 0 ; //is used inside the opendir function
uint8_t argv_index_beg2 = 0 ; 


//function that handle the input 
void options (int argc , char** argv )
{
    

    //options must be supported -latucifd1
    int  opt ;
    f_noopt=1;
    while ( (opt = getopt(argc,argv,"latucifd1")) != -1 )
    {
        f_noopt = 0;
        #ifdef debug
            printf("opt=%d (%c) , optind = %d\n",opt,printable(opt),optind);
        #endif
        switch(opt)
        {
            case 'l' : f_l = 1 ; break; 
            case 'a' : f_a = 1 ; break; 
            case 't' : f_t = 1 ; break; 
            case 'u' : f_u = 1 ; break; 
            case 'c' : f_c = 1 ; break; 
            case 'i' : f_i = 1 ; break; 
            case 'f' : f_f = 1 ; break; 
            case 'd' : f_d = 1 ; break; 
            case '1' : f_1 = 1 ; break; 
            case '?' : f_error=1; break;
            case ':' : f_error=1; break;
        }
    }
    
}


//function that get open the dir and read it's content 
int dir_table (int argc , char** argv,all_info** nodes)
{
    argv_index_beg1=optind;
    optind++;
    DIR* dp ;
    // if(argv[argv_index_beg1] == NULL)
    // {
    //     // use the current working directory
    //     dp =opendir(".");
    // }    
    //else
        dp =opendir(argv[argv_index_beg1]);
    if(dp == NULL )
    {
        perror("opening directory");
        exit(0);
    }
    struct dirent* entry = readdir(dp);
    if(entry == NULL && errno != 0)
    {
        perror("readdir failed");
        exit(0);
    }
    // a3mel malloc lel size of direc_struct * initail no 
    int size_unit = 10 ;
    *nodes = (all_info*)malloc(sizeof(all_info)*size_unit);
    if(*nodes == NULL)
    {
        perror("malloc failed");
    }
    all_info* copy_struct = *nodes;

    int count=-1 ; 
    do 
    {
        count++;
        copy_struct->dir_info.inode_no = entry->d_ino ;
        copy_struct->dir_info.d_name  = strdup(entry->d_name);
        copy_struct++;
        if(count >= size_unit )
        {
            size_unit += 10 ;
            *nodes=(all_info*)realloc(nodes,size_unit*sizeof(all_info));
            if(*nodes == NULL)
            {
                perror("malloc failed");
            }
        }
        entry = readdir(dp);
        if(entry == NULL && errno != 0)
        {
            perror("readdir failed");
            exit(0);
        }
        
    }while(entry != NULL );
    closedir(dp);
    return count ;
}

// function to get inode info
void inode_info(char** argv, int no_entry, all_info** nodes) {
    all_info* carry = *nodes;
    char argv_copy[4096]; // Buffer to hold the full path

    for (int i = 0; i <= no_entry; i++) {
        // Create a copy of the directory path
        snprintf(argv_copy, sizeof(argv_copy), "%s/%s", argv[argv_index_beg1], carry->dir_info.d_name);

        // Retrieve inode information using lstat
        if (lstat(argv_copy, &carry->inode_info) == -1) {
            perror("lstat");
            continue; // Continue to the next entry in case of an error
        }

        // Print inode information
        #ifdef debug
        printf("\nmode: %o\n", carry->inode_info.st_mode);
        printf("link count: %ld\n", carry->inode_info.st_nlink);
        printf("user: %d\n", carry->inode_info.st_uid);
        printf("group: %d\n", carry->inode_info.st_gid);
        printf("size: %ld\n", carry->inode_info.st_size);
        printf("modtime: %ld\n", carry->inode_info.st_mtime);
        printf("name: %s\n", argv_copy);
        printf("\n");
        #endif
        carry++; // Move to the next entry
    }
}



