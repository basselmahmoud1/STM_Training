#include"functions.h"



int main (int argc , char** argv)
{
    // making some variable that is used inside the code (copy of the index of the first element)
    
    options(argc,argv);
    #ifdef debug
    printf("index of the first arg is = %d\n",optind);
    #endif
    //check how many dir to list
    
    uint8_t counter = 0 ;
    if(argv[optind] == NULL)
        counter++;

    uint8_t index = optind ;

    while(argv[index] != NULL )
    {
        counter ++ ; 
        index ++ ;
    }
    if(argv[optind] == NULL)
        argv[1]= ".";
    // loop on counts to implement ls
    while (counter--)
    {
        #ifdef debug
            printf("counter %d \n",counter);
        #endif
        //prepare the data to be printed 
        
        // open the dir and get the entry (inode no and name )
        all_info* nodes = NULL;
        int no_entry=0 ;
        no_entry=dir_table(argc,argv,&nodes);
        

        // read all of the inodes and save them inside an array of structures 
        inode_info (argv, no_entry,&nodes);
        // for(int i = 0 ; i<=no_entry ;i++)
        // {
        //     printf("name:%s ,inode:%ld\n",copy_struct_inode_name->d_name,copy_struct_inode_name->inode_no);
        //     copy_struct_inode_name++;
        // }
        if(f_noopt)
        {
            all_info* copy_struct_nodes = nodes;
            for(int i = 0 ; i <= no_entry ; i++)
            {
                if(copy_struct_nodes->dir_info.d_name[0]=='.')
                {
                    copy_struct_nodes++;
                    continue;
                }
                printf("%s\t",copy_struct_nodes->dir_info.d_name);
                copy_struct_nodes++;
            }
            printf("\n");

            free(nodes);
            continue;

        }
        // dont forget to free the inode_names
        free(nodes);

    } 

    return 0 ;
}