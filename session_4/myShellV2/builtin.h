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

#define PATH_MAX	4096 

void perform_builtin(int argc,char **argv);

void help (int argc,char **argv);

void echo (int argc , char **argv);

void pwd (int argc ,char **argv );


#endif
