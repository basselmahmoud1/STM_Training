#include "builtin.h"


void perform_builtin(int argc,char **argv)
{
	if (argc != 0)
	{
		if(strcmp(argv[0],"mypwd")==0)
		{
			char * carry =pwd (argc,argv);
			write_usr( carry , strlen(carry) ) ;
			write_usr("\n", strlen("\n") );
		}
		else if(strcmp(argv[0],"echo")==0)
		{
			echo (argc,argv);
		}
		else if(strcmp(argv[0],"mycp")==0)
		{
			cp (argc , argv);
		}
		else if(strcmp(argv[0],"mymv")==0)
		{
			mv(argc , argv);
		}
		else if(strcmp(argv[0],"exit")==0)
		{
			exit_usr();
		}
		else if(strcmp(argv[0],"help")==0)
		{
			help(argc,argv);
		}
		else if(strcmp(argv[0],"type")==0)
		{
			switch (type(argc,argv[1]))
			{
			// check if it is  external (if true dont enter builtin perform func)
		      		case EXTERNAL :	write_usr("External command\n",strlen("External command\n")); 	break;
			//check if builtin function
				case INTERNAL :	write_usr("Internal command\n",strlen("Internal command\n"));	break;
			// nethier generate un supported func
				case UN_SUPP : write_usr("command isnt supported\n", strlen("command isnt supported\n") ); break;
			}
					
		}
		else if(strcmp(argv[0],"envir")==0)
		{
			envir();
		}
		
		else if (strcmp(argv[0],"cd")==0)
		{
			char * carry = cd (argc,argv);
			write_usr( carry , strlen(carry) ) ;
			write_usr("\n", strlen("\n") );
		}
		else
		{
			write_usr("command isnt supported\n", strlen("command isnt supported\n") );

		}



	}

	else
		return ;

}


void help (int argc,char **argv)
{
	if (argc == 1 )
		write_usr("help command dispaly explaination of each command\n", strlen("help command dispaly explaination of each command\n") );
	else if (strcmp(argv[1],"mycp")==0)
		write_usr("cp : copy a file given (1st argumment) into the other file (2nd argumment)\n",strlen("cp : 					copy a file given (1st argumment) into the other file (2nd argumment)\n"));
	else if (strcmp(argv[1],"echo")==0)
		write_usr("echo : print back the string given\n",strlen("echo : print back the string given\n"));
	else if (strcmp(argv[1],"mypwd")==0)
		write_usr("pwd : prints the current working directory\n",strlen("pwd : prints the current working directory\n"));
	else if (strcmp(argv[1],"mymv")==0)
		write_usr("mv : move file to another directory\n",strlen("mv : move file to another directory\n"));
	else if (strcmp(argv[1],"exit")==0)
		write_usr("exit : terminates the shell\n",strlen("exit : terminates the shell\n"));
	else if (strcmp(argv[1],"type")==0)
		write_usr("type : gives you the type of command\nExternal\nInternal\nunsupported\n",strlen("type : gives you the type of command\nExternal\nInternal\nunsupported\n"));
	else if (strcmp(argv[1],"help")==0)
		write_usr("supported builtin commands are:\nhelp\nexit\nmv\npwd\necho\ncp\n",strlen("supported builtin commands are:\nhelp\nexit\nmv\npwd\necho\ncp\n"));
	else if (strcmp(argv[1],"cd")==0)
		write_usr("cd : change working directory\n",strlen("cd : change working directory\n"));
	else if (strcmp(argv[1],"envir")==0)
		write_usr("envir : print all environment variables\n",strlen("envir : print all environment variables\n"));
}




void echo (int argc , char **argv)
{
	int counter = 1 ;

	if (argc < 2) {
		write_usr("\n", strlen("\n"));
		return;
	}

	while ( argv[counter] != NULL )
	{
		write_usr( argv[counter] , strlen( argv[counter] ) );
		write_usr(" ", strlen(" ") );
		counter++;
	}
	write_usr("\n", strlen("\n") );
}


char* pwd (int argc ,char **argv )
{

	char *error_state;
	char CWD [PATH_MAX];
	char *cpy ;
	error_state = getcwd ( CWD , PATH_MAX );

	if(error_state == NULL)
	{
		perror("pwd:");
		error_checker = 1 ;
	}
	cpy = strdup (CWD);
	
	return cpy;
}

void exit_usr (void)
{

	write_usr("SALAM YA NIGM :( \n",strlen("SALAM YA NIGM :( \n"));
	exit(0);

}







void cp (int argc , char ** argv) 
{
	char buffer [100] ;
	char *source_name ;
	ssize_t count_S , count_T ;
	int i =0 , flag = 0 , flag_option=0;
	int fd_T = 0 ,fd_S = 0; 
	
	
	
	
	
	
	
	
	if( strcmp(argv[1],"-a") == 0 )
	{
		if(argc == 4)
			flag_option = 1;
		else
		{
			write_usr(" error :missing arguments \n",strlen("error :missing arguments \n"));
			return;
		}		
		if (strcmp(argv[3], ".")==0)
		{
			argv[3]=pwd(argc,argv);
		}
	}
	else 
	{	
		if(argc == 3)
			flag_option = 0 ;
		else
		{
			write_usr(" error :missing arguments \n",strlen("error :missing arguments \n"));
			return;
		}
		if (strcmp(argv[2], ".")==0)
		{
			argv[2]=pwd(argc,argv);
		}
	
	}
	
	
	if(flag_option == 1)
	{
		
			
			 fd_S = open (argv[2] ,O_RDONLY  );	
			 
			 if( argv[3][strlen(argv[3])-1] == '/' )  //directory checking
			{
				for( i = strlen(argv[2])-1  ; i >= 0 ; i--)
				{
					if (argv[2][i] == '/')
					{
						source_name = argv[2] + i +1 ;
						flag=1;
						break;
					}
				}
				if(flag==0)
					source_name = argv[2]  ;
			
				strcat(argv[3],source_name);
			}
			
			fd_T = open ( argv[3] , O_RDWR|O_CREAT| O_APPEND , S_IRUSR | S_IWUSR ) ;
	}
	else
	{
		 
		 fd_S = open (argv[1] ,O_RDONLY  );
		
		if( argv[2][strlen(argv[2])-1] == '/' )
		{
			for( i = strlen(argv[1])-1  ; i >= 0 ; i--)
			{
				if (argv[1][i] == '/')
				{
					source_name = argv[1] + i +1 ;
					flag=1;
					break;
				}
			}
		
			if(flag==0)
				source_name = argv[1]  ;
		
			strcat(argv[2],source_name);
		
		}
	
		fd_T = open ( argv[2] , O_RDWR|O_CREAT| O_TRUNC |O_EXCL , S_IRUSR | S_IWUSR ) ;
	}
	
	
	if (fd_S ==-1)
	{
		perror ("open source file:");
		error_checker = 1;
		return;
	}
	
	/*if( argv[2][strlen(argv[2])-1] == '/' )
	{
		for( i = strlen(argv[1])-1  ; i >= 0 ; i--)
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
	}*/
	
	
	
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
			return ;
		}	
	}
	
	if(count_S == -1)
	{
			perror ("read source:");
			error_checker = 1 ;
			return ;
	}	
	
	if(close(fd_S) == -1)
	{
		perror ("close source file:");
		error_checker = 1;
		return ;
	}
	if(close(fd_T) == -1)
	{
		perror ("close target file:");
		error_checker = 1;
		return ;
	}
	
	
		
}

void mv (int argc , char ** argv)
{
	char buffer [100] ;
	char *source_name ;
	ssize_t count_S , count_T ;
	int i =0 , flag = 0 ,flag_option=0 ;
	int fd_T = 0 ,fd_S = 0 ,error_state = 0;
	
	
	
	
	if( strcmp(argv[1],"-f") == 0 )
	{
		if(argc == 4)
			flag_option = 1;
		else
		{
			write_usr(" error :missing arguments \n",strlen("error :missing arguments \n"));
			return;
		}		
		if (strcmp(argv[3], ".")==0)
		{
			argv[3]=pwd(argc,argv);
		}
	}
	else 
	{	
		if(argc == 3)
			flag_option = 0 ;
		else
		{
			write_usr(" error :missing arguments \n",strlen("error :missing arguments \n"));
			return;
		}
		if (strcmp(argv[2], ".")==0)
		{
			argv[2]=pwd(argc,argv);
		}
	
	}
	
	
	if(flag_option == 1)
	{
		 fd_S = open (argv[2] ,O_RDONLY  );	
		// getting source name 	
		
		
		 
		 if( argv[3][strlen(argv[3])-1] == '/' )
		{
			for( i = strlen(argv[2])-1  ; i >= 0 ; i--)
			{
				if (argv[2][i] == '/')
				{
					source_name = argv[2] + i +1 ;
					flag=1;
					break;
				}
			}
			if(flag==0)
				source_name = argv[2]  ;
			
			strcat(argv[3],source_name);
		}
		
		fd_T = open ( argv[3] , O_RDWR|O_CREAT| O_TRUNC , S_IRUSR | S_IWUSR ) ;
	
	}
	
	else
	{
		 
		 fd_S = open (argv[1] ,O_RDONLY  );
		
		if( argv[2][strlen(argv[2])-1] == '/' )
		{
			for( i = strlen(argv[1])-1  ; i >= 0 ; i--)
			{
				if (argv[1][i] == '/')
				{
					source_name = argv[1] + i +1 ;
					flag=1;
					break;
				}
			}
		
			if(flag==0)
				source_name = argv[1]  ;
		
			strcat(argv[2],source_name);
		
		}
	
		fd_T = open ( argv[2] , O_RDWR|O_EXCL|O_CREAT , S_IRUSR | S_IWUSR ) ;
	}
	
	
	
	//int fd_S = open (argv[1] ,O_RDONLY  );
	if (fd_S ==-1)
	{
		perror ("open source file:");
		error_checker = 1;
		return;
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
			return;
		}	
	}
	
	if(flag_option == 0)
	{
		error_state = remove( argv[1] );
		if ( error_state != 0)
		{
			perror("remove file:");
			error_checker = 1;
			return;
		}
	}
	else
	{
		error_state = remove( argv[2] );
		if ( error_state != 0)
		{
			perror("remove file:");
			error_checker = 1;
			return;
		}
	}
			
			
			
			
	if(count_S == -1)
	{
			perror ("read source:");
			error_checker = 1 ;
			return;
	}	
	
	if(close(fd_S) == -1)
	{
		perror ("close source file:");
		error_checker = 1;
		return;
	}
	if(close(fd_T) == -1)
	{
		perror ("close target file:");
		error_checker = 1;
		return;
	}
}

char * cd (int argc , char ** argv)
{
	char *carry ;
	if(argc <= 1)
		write_usr("missing arrgument\n",strlen("missing arrgument\n"));
	int error_state = chdir(argv[1]);
	if(error_state != 0)
	{
		perror("changing directory");
		error_checker = 1 ;
		return NULL ;
	}

	carry = pwd(argc,argv) ;
	return carry ;

	
}


void envir (void) 
{
	int i=0;
	while ( (environ[i]!=NULL) )
	{
		write_usr(environ[i],strlen(environ[i]));
		write_usr("\n",strlen("\n"));
		i++;
	}
}


void env_var ( int argc , char ** argv )
{
	int len = strlen(argv[0]);
	int i ;
	char *arr ;
	arr = strdup(argv[0]);
	
	for(i=0 ; i < len ; i++)
	{
		if(arr[0] !=  '\0')
		arr[i] = arr[i+1];
	}
	arr[i-1] ='\0'; 
	//write_usr(arr,strlen(arr));
	char *value = getenv(arr);
	write_usr(value,strlen(value));
	write_usr("\n",strlen("\n"));
}










