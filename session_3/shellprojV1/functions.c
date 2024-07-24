
#include "functions.h"


int  counter;
int error_checker = 0;

const char *shellmsg ="n3m ya 8aly > ";

char *tokens[5];
char command[101];
char CWD [PATH_MAX];


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


void pwd (void)
{
	char *error_state;
	error_state = getcwd ( CWD , PATH_MAX );
	
	if(error_state == NULL)
	{
		perror("pwd:");
		error_checker = 1 ;
	}
	
	//write_usr("\n", strlen("\n") );
	write_usr( CWD , strlen(CWD) ) ;
	write_usr("\n", strlen("\n") );

}

void echo (void)
{
	counter = 1 ;
	
	while ( tokens[counter] != NULL )
	{
		write_usr( tokens[counter] , strlen( tokens[counter] ) );
		write_usr(" ", strlen(" ") );
		counter++;
	}
	write_usr("\n", strlen("\n") );
	
}





void cp (void) 
{
	char buffer [100];
	ssize_t count_S , count_T ;
	
	int fd_S = open (tokens[1] ,O_RDONLY  );
	if (fd_S ==-1)
	{
		perror ("open source file:");
		error_checker = 1;
	}
	
	int fd_T = open ( tokens[2] , O_RDWR|O_CREAT|O_TRUNC , S_IRUSR | S_IWUSR ) ;
	if (fd_T ==-1)
	{
		perror ("creating target file:");
		error_checker = 1;
	}
	
	do
	{
		count_S = read (fd_S , buffer , 100 );
		if(count_S == -1)
			perror ("read source:");
			
		write (fd_T ,buffer ,100 );
		if(count_T == -1) 
			perror ("read source:");
			
	}while ( count_S != 0 );
	
	
	if(close(fd_S) == -1)
	{
		perror ("close source file:");
		error_checker = 1;
	}
	if(close(fd_T) == -1)
	{
		perror ("close target file:");
		error_checker = 1;
	}
		
}



void perform_comm (void) 
{

	if(strcmp(tokens[0],"pwd\n")==0)
	{
	//	write_usr("pwd is entered\n", strlen("pwd is entered\n") );
		pwd ();
	}
	
	if(strcmp(tokens[0],"echo")==0)
	{
		write_usr("echo is entered\n", strlen("echo is entered\n") );
		echo ();
	}
	
	if(strcmp(tokens[0],"cp")==0)
	{
		cp();
		//write_usr("cp is entered\n", strlen("cp is entered\n") );
	}
	
	if(strcmp(tokens[0],"mv")==0)
	{
		write_usr("mv is entered\n", strlen("mv is entered\n") );
	}
	
	
	
	if(strcmp(tokens[0],"help")==0)
	{
		write_usr("help is entered\n", strlen("help is entered\n") );
	}
	
	if(strcmp(tokens[0],"exit")==0)
	{
		write_usr("exit is entered\n", strlen("exit is entered\n") );
	}
	
	
	

}



