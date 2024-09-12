

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
#include <grp.h>


#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')
#define debug2

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
typedef enum mode{
    //format
    short_formate,
    long_formate,
    // time modes
    accesstime,
    modificationtime,
    changetime,
    //sort technique
    sort_name,
    sort_access_time ,
    sort_mod_time ,
}mode;


extern uint8_t argv_index_beg1,argv_index_beg2 ;
extern char *optarg;
extern int optind, opterr, optopt;
extern uint8_t f_l , f_a , f_t , f_u, f_c, f_i, f_f, f_d, f_1,f_noopt,f_error,f_showaccess,f_showmod,f_symlink,f_multipesource;



void options (int argc , char** argv );

int dir_table (int argc , char** argv,all_info** inode_names);

void inode_info (char** argv,int no_entry,all_info** nodes);

//make helping functions to help in printing 

//map the user and group id to there name 
const char* uid_to_name ( all_info* node  );
const char* gid_to_name ( all_info* node  );
const char* filetype_conversion (all_info* node,mode type );
const char* permissions (all_info* node);
const char *time_conversion (all_info *node, mode type);
//compare algorithms 
static int cmp_name (const void *p1, const void *p2);
static int cmp_time_mod (const void *p1, const void *p2);
static int cmp_time_access (const void *p1, const void *p2);
void sort_nodes (all_info* nodes,int no_entry,mode type);
//API of implementation 
void sort_flags(all_info* nodes,int no_entry);
void print_time (all_info* node);
void print_file_name (all_info* node,char** argv,int counter);



#endif
