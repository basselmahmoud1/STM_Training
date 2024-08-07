#ifndef EXTERNAL_H
#define EXTERNAL_H




#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include  <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "functions.h"

typedef struct{
pid_t PID;
char * name ;
char * exit_status ;
}process;


extern process history [10] ;
extern int process_count ;
extern int error_checker ;


void perform_EXT (int argc,char** argv);

void addProcessToHistory (pid_t CPID , char* p_name ,  int state ,char ** argv );




#endif
