#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include  <stddef.h>



#define STDIN  0
#define STDOUT 1
#define STDERR 2
 
const char *shellmsg ="n3m ya 8aly>";

char *tokens[5];
char commands[101];

/*typedef enum
{
pwd ,
echo , 
cp ,
mv ,
help 
}supp_commands;*/

int  counter;
int error_checker = 0;
//supp_commands given_command ;




void read_usr (void);

void write_usr ( const char *buffer , size_t count);

void perform_comm (void);


#endif
