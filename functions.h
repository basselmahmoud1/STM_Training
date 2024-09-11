#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <inttypes.h>

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')
#define debug 

typedef struct direc_struct
{
    ino_t inode_no;
    char*  d_name;
}direc_struct;
typedef struct all_info
{
    direc_struct dir_info;
    struct stat inode_info;
}all_info;


extern uint8_t argv_index_beg1,argv_index_beg2 ;
extern char *optarg;
extern int optind, opterr, optopt;
extern uint8_t f_l , f_a , f_t , f_u, f_c, f_i, f_f, f_d, f_1,f_noopt,f_error;



void options (int argc , char** argv );

int dir_table (int argc , char** argv,all_info** inode_names);

void inode_info (char** argv,int no_entry,all_info** nodes);




#endif