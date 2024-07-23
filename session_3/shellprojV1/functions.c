
#include "functions.h"


int  counter;
int error_checker = 0;

const char *shellmsg ="n3m ya 8aly>";

char *tokens[5];
char command[101];


void read_usr (void)
{
	ssize_t readsize = 0;
	readsize = read (STDIN,command,100);	
	
	if (readsize == -1)
	{
		perror("read:");
		error_checker = 1;
	}
	command [readsize+1]='\0';
	
	*tokens = strtok(command , " ");
	counter = 0 ;
	while(tokens[counter] != NULL )
		{
			counter ++ ;
			tokens[counter] = strtok(NULL," ");
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

void perform_comm (void) 
{
	
	if(strcmp(tokens[0],"cp")==0)
	{
		write_usr("cp is entered",15);
	}
	
	if(strcmp(tokens[0],"mv")==0)
	{
		write_usr("mv is entered",15);
	}
	
	if(strcmp(tokens[0],"pwd")==0)
	{
		write_usr("pwd is entered",16);
	}
	
	if(strcmp(tokens[0],"help")==0)
	{
		write_usr("help is entered",20);
	}
	
	if(strcmp(tokens[0],"exit")==0)
	{
		write_usr("exit is entered",15);
	}
	

}



