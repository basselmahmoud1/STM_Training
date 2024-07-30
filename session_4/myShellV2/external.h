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


extern int error_checker ;


void perform_EXT (int argc,char** argv);




#endif
