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


#define PATH_MAX	4096 

extern char ** environ;
//extern process history[10] ;

void perform_builtin(int argc,char **argv);

void help (int argc,char **argv);

void echo (int argc , char **argv);

extern int type (int argc , char*argv);

char * pwd (int argc ,char **argv );

void exit_usr (void);

void cp (int argc , char ** argv);

void mv (int argc , char ** argv);

char * cd (int argc , char ** argv);

void envir (void) ;

void env_var ( int argc , char ** argv );

void ps (const process *history );

#endif
