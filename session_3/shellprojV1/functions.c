
#include "functions.h"


int  counter;
int error_checker = 0;

const char *shellmsg ="engez mafesh w2t lel tafser $> ";

char *tokens[5];
char command[1001];
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
	if(readsize>1)
		command [readsize-1]='\0';
	else 
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
	char buffer [100] ;
	char *source_name ;
	ssize_t count_S , count_T ;
	int i =0 , flag = 0 ;
	int fd_T = 0 ,fd_S = 0; 
	
	
	
	if(tokens[2]==NULL || tokens[1] == NULL)
	{
		write_usr("Error : missing arrgument\n",strlen("Error : missing arrgument\n"));
		return;
	}
	
	if( strcmp(tokens[1],"-a") == 0 )
	{
		if(tokens[3]==NULL || tokens[2] == NULL)
		{
			write_usr("Error : missing arrgument\n",strlen("Error : missing arrgument\n"));
			return;
		}
		
		 fd_S = open (tokens[2] ,O_RDONLY  );	
		 
		 if( tokens[3][strlen(tokens[3])-1] == '/' )
		{
			for( i = strlen(tokens[2])-1  ; i >= 0 ; i--)
			{
				if (tokens[2][i] == '/')
				{
					source_name = tokens[2] + i +1 ;
					flag=1;
					break;
				}
			}
			if(flag==0)
				source_name = tokens[2]  ;
		
			strcat(tokens[3],source_name);
		}
		
		fd_T = open ( tokens[3] , O_RDWR|O_CREAT| O_APPEND , S_IRUSR | S_IWUSR ) ;
	
	}
	
	else
	{
		 
		 fd_S = open (tokens[1] ,O_RDONLY  );
		
		if( tokens[2][strlen(tokens[2])-1] == '/' )
		{
			for( i = strlen(tokens[1])-1  ; i >= 0 ; i--)
			{
				if (tokens[1][i] == '/')
				{
					source_name = tokens[1] + i +1 ;
					flag=1;
					break;
				}
			}
		
			if(flag==0)
				source_name = tokens[1]  ;
		
			strcat(tokens[2],source_name);
		
		}
	
		fd_T = open ( tokens[2] , O_RDWR|O_CREAT| O_TRUNC |O_EXCL , S_IRUSR | S_IWUSR ) ;
	}
	
	
	if (fd_S ==-1)
	{
		perror ("open source file:");
		error_checker = 1;
	}
	
	if( tokens[2][strlen(tokens[2])-1] == '/' )
	{
		for( i = strlen(tokens[1])-1  ; i >= 0 ; i--)
		{
			if (tokens[1][i] == '/')
			{
				source_name = tokens[1] + i +1 ;
				flag=1;
				break;
			}
		}
		
		if(flag==0)
			source_name = tokens[1]  ;
		
		strcat(tokens[2],source_name);
	}
	
	
	
	if (fd_T ==-1)
	{
		perror ("creating target file:");
		error_checker = 1;
		close(fd_S);
		return ;
	}
	
	while ( (count_S = read (fd_S , buffer , sizeof(buffer) )) > 0 )
	{
		
		count_T = write (fd_T ,buffer ,count_S );
		if(count_T == -1)
		{ 
			perror ("read source:");
			error_checker =1 ;
			break;
		}	
	}
	
	if(count_S == -1)
	{
			perror ("read source:");
			error_checker = 1 ;
	}	
	
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


void mv (void)
{
	char buffer [100] ;
	char *source_name ;
	//char *target_name ;
	ssize_t count_S , count_T ;
	int i =0 , flag = 0 ;
	int fd_T = 0 ,fd_S = 0 ,error_state = 0;
	
	if(tokens[2]==NULL || tokens[1] == NULL)
	{
		write_usr("Error : missing arrgument\n",strlen("Error : missing arrgument\n"));
		return;
	}
	
	if( strcmp(tokens[1],"-f") == 0 )
	{
		if(tokens[3]==NULL || tokens[2] == NULL)
		{
			write_usr("Error : missing arrgument\n",strlen("Error : missing arrgument\n"));
			return;
		}
		
		
		
		 fd_S = open (tokens[2] ,O_RDONLY  );	
		
		// getting source name 
		
		for( i = strlen(tokens[2])-1  ; i >= 0 ; i--)
			{
				if (tokens[2][i] == '/')
				{
					source_name = tokens[2] + i +1 ;
					flag=1;
					break;
				}
			}
		if(flag==0)
				source_name = tokens[2]  ;
		
		 
		 if( tokens[3][strlen(tokens[3])-1] == '/' )
		{
			
			strcat(tokens[3],source_name);
		}
		
		fd_T = open ( tokens[3] , O_RDWR|O_CREAT| O_TRUNC , S_IRUSR | S_IWUSR ) ;
		
		
		
	
	}
	
	else
	{
		 
		 fd_S = open (tokens[1] ,O_RDONLY  );
		
		if( tokens[2][strlen(tokens[2])-1] == '/' )
		{
			for( i = strlen(tokens[1])-1  ; i >= 0 ; i--)
			{
				if (tokens[1][i] == '/')
				{
					source_name = tokens[1] + i +1 ;
					flag=1;
					break;
				}
			}
		
			if(flag==0)
				source_name = tokens[1]  ;
		
			strcat(tokens[2],source_name);
		
		}
	
		fd_T = open ( tokens[2] , O_RDWR|O_CREAT|O_EXCL , S_IRUSR | S_IWUSR ) ;
	}
	
	
	
	//int fd_S = open (tokens[1] ,O_RDONLY  );
	if (fd_S ==-1)
	{
		perror ("open source file:");
		error_checker = 1;
	}
	
	
	
	
	
	
	//int fd_T = open ( tokens[2] , O_RDWR|O_CREAT|O_EXCL , S_IRUSR | S_IWUSR ) ;
	if (fd_T ==-1)
	{
		perror ("creating target file:");
		error_checker = 1;
		close(fd_S);
		return ;
	}
	
	while ( (count_S = read (fd_S , buffer , sizeof(buffer) )) > 0 )
	{
		
		count_T = write (fd_T ,buffer ,count_S );
		if(count_T == -1)
		{ 
			perror ("read source:");
			error_checker =1 ;
			break;
		}	
	}
	
	if(strcmp(tokens[1],"-f") != 0 )
	{
		error_state = remove( tokens[1] );
		if ( error_state != 0)
		{
			perror("remove file:");
			error_checker = 1;
		}
	}
	else
	{
		error_state = remove( tokens[2] );
		if ( error_state != 0)
		{
			perror("remove file:");
			error_checker = 1;
		}
	}
			
			
			
			
	if(count_S == -1)
	{
			perror ("read source:");
			error_checker = 1 ;
	}	
	
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



void exit_usr (void)
{

	write_usr("SALAM YA NIGM :( \n",strlen("SALAM YA NIGM :( \n"));
	exit(0);

	
}


void help (void) 
{
	write_usr("supported commands are :\n",strlen("supported commands are :\n"));
	write_usr("pwd : prints the current working directory\n",strlen("pwd : prints the current working directory\n"));
	write_usr("echo : print back the string given\n",strlen("echo : print back the string given\n"));
	write_usr("cp : copy a file given (1st argumment) into the other file (2nd argumment)\n",strlen("cp : copy a file given (1st argumment) into the other file (2nd argumment)\n"));
	write_usr("mv : move file to another directory\n",strlen("mv : move file to another directory\n"));
	write_usr("exit : terminates the shell\n",strlen("exit : terminates the shell\n"));
}



void perform_comm (void) 
{

	if(strcmp(tokens[0],"pwd")==0)
	{
	//	write_usr("pwd is entered\n", strlen("pwd is entered\n") );
		pwd ();
	}
	
	else if(strcmp(tokens[0],"echo")==0)
	{
	//	write_usr("echo is entered\n", strlen("echo is entered\n") );
		echo ();
	}
	
	else if(strcmp(tokens[0],"cp")==0)
	{
		cp();
		//write_usr("cp is entered\n", strlen("cp is entered\n") );
	}
	
	else if(strcmp(tokens[0],"mv")==0)
	{
		//write_usr("mv is entered\n", strlen("mv is entered\n") );
		mv();
	}
	
	
	else if(strcmp(tokens[0],"exit")==0)
	{
		//write_usr("exit is entered\n", strlen("exit is entered\n") );
		exit_usr();
	}
	
	
	else if(strcmp(tokens[0],"help")==0)
	{
		//write_usr("help is entered\n", strlen("help is entered\n") );
		help();
	}
	else if(strcmp(tokens[0],"\n")==0)
	{
		return;
	}
	else
	{
		write_usr("command isnt supported\n", strlen("command isnt supported\n") );
	
	}
	
	
	
	

}



