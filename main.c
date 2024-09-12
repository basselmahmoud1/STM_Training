#include "functions.h"

int main(int argc, char **argv)
{
    // making some variable that is used inside the code (copy of the index of the first element)

    options(argc, argv);
#ifdef debug
    printf("index of the first arg is = %d\n", optind);
#endif
    // check how many dir to list

    uint8_t counter = 0;
    if (argv[optind] == NULL)
        counter++;

    uint8_t index = optind;

    while (argv[index] != NULL)
    {
        counter++;
        index++;
    }
    if (argv[optind] == NULL)
        argv[optind] = ".";
    // loop on counts to implement ls
    argv_index_beg2 = index ; 
    while (counter--)
    {
        #ifdef debug
        printf("counter %d \n", counter);
        #endif
        // prepare the data to be printed

        // open the dir and get the entry (inode no and name )
        all_info *nodes = NULL;
        int no_entry = 0;
        no_entry = dir_table(argc, argv, &nodes);

        // read all of the inodes and save them inside an array of structures
        inode_info(argv, no_entry, &nodes);

        if(f_l == 1)
        {   
            /************************print in long format **********************/
            // determine the sorting algorithm
            all_info *copy_struct_nodes = nodes;
            sort_flags(nodes,no_entry);
            for(int i = 0 ; i <= no_entry ; i++ )
            {
                if(f_a == 0)
                {
                    if(copy_struct_nodes->dir_info.d_name[0] == '.')
                    {
                        copy_struct_nodes++;
                        continue;
                    }
                }
                //check if the inode no will be printed
                if(f_i)
                    printf("%ld  ",copy_struct_nodes->dir_info.inode_no);
                //print the file type & it's permissions
                printf("%s%s ",
                    filetype_conversion(copy_struct_nodes,short_formate),
                    permissions(copy_struct_nodes)
                );
                //print no of hard links 
                printf("%ld ",copy_struct_nodes->inode_info.st_nlink);

                //print owner & group name  
                printf("%s %s ",uid_to_name(copy_struct_nodes),gid_to_name(copy_struct_nodes) );

                //print size of the file

                printf("%ld ",(uint64_t)copy_struct_nodes->inode_info.st_size);

                //print time 
                print_time(copy_struct_nodes);

                //print file name 

                print_file_name(copy_struct_nodes,argv,counter);

                copy_struct_nodes ++ ;
            }



        }
        else
        {
            /************************print in short format **********************/
        }

        
        if(counter != 0)
            printf("\n\n");
        // dont forget to free the inode_names
        free(nodes);
    }

    return 0;
}















// if (f_noopt)
//         {
//             all_info *copy_struct_nodes = nodes;
//             for (int i = 0; i <= no_entry; i++)
//             {
//                 if (copy_struct_nodes->dir_info.d_name[0] == '.')
//                 {
//                    // copy_struct_nodes++;
//                     //continue;
//                 }
//                 printf("%s\t", copy_struct_nodes->dir_info.d_name);
//                 copy_struct_nodes++;
//             }
//             printf("\n");

//             free(nodes);
//             continue;
//         }