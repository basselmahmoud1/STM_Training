#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include  <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>


#define STDIN  		0
#define STDOUT 		1
#define STDERR 		2
#define COMM_SIZE 	1001
#define EXTERNAL 	0
#define INTERNAL	1
#define UN_SUPP		-1
#define PATH_MAX	4096 
extern const char *shellmsg ;


extern char command[COMM_SIZE];



extern int  counter;
extern int error_checker ;

void read_usr (void);
int get_tokens_num (const char * buff );
char ** get_tokens (const char * buff );
void write_usr ( const char *buffer , size_t count);
int type (int argc ,char * argss);
void redirections (int argc , char ** argv );
void env_var ( int argc , char ** argv , int loc);
void set_env_var(int argc,char ** argv);



#endif
