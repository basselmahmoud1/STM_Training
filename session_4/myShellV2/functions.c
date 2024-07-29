#include "functions.h"


int  counter;
int error_checker = 0;
int argc ;
char * argv[] ;
char * commands; 

const char *shellmsg ="engez mafesh w2t lel tafser $> ";


void read_usr (void)
{
	ssize_t readsize = 0;
	readsize = read (STDIN,command,100);	
	
	if (readsize == -1)
	{
		perror("read:");
		error_checker = 1;
	}
	if(readsize>1)
		command [readsize-1]='\0';
	else 
		command [readsize+1]='\0';
	
		
}

void get_tokens_num (const char * buff )
{
	char *tokens ;
	tokens = strtok( buff , " " );
	while (tokens[argc] != NULL )
	{
		argc++;
		tokens[argc] = strtok( NULL , " " ); 
	}
}

void get_tokens (const char * buff )
{
	char **tokens = malloc(argc * sizeof(char*)) ;
	tokens = strtok( buff , " " );
	while (token[argc] != NULL )
	{
		argc++;
		tokens[argc] = strtok( NULL , " " ); 
	}
	
}



void write_usr ( const char *buffer , size_t count)
{
	ssize_t writesize = write (STDOUT , buffer , count) ;
	
	if( writesize == -1 )
	{
		perror("write:");
		error_checker = 1;
	}
	
}
