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
 
extern const char *shellmsg ;

extern char *tokens[5];
extern char command[101];

/*typedef enum
{
pwd ,
echo , 
cp ,
mv ,
help 
}supp_commands;*/

extern int  counter;
extern int error_checker ;
//supp_commands given_command ;




void read_usr (void);

void write_usr ( const char *buffer , size_t count);

void perform_comm (void);


#endif
