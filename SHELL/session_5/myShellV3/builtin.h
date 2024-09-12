#ifndef BUILTIN_H
#define BUILTIN_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include  <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "functions.h"
#include "external.h"
#include <sys/sysinfo.h>


#define PATH_MAX	4096 




extern operant op ;

extern char ** environ;
//extern process history[10] ;

void perform_builtin(int argc,char** argv,operant op , int loc);

void help (int argc,char **argv);

void echo (int argc , char **argv);

extern int type (int argc , char*argv);

char * pwd (int argc ,char **argv );

void exit_usr (void);

void cp (int argc , char ** argv);

void mv (int argc , char ** argv);

char * cd (int argc , char ** argv);

void envir (void) ;

void ps (const process *history );

void myfree (int argc , char ** argv);

void myuptime (void);

#endif
