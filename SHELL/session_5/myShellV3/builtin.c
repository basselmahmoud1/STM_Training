#include "builtin.h"

//extern process history [10];
//extern int process_count ;



void perform_builtin(int argc,char** argv,operant op , int loc)
{

	
	if (argc != 0)
	{
	
		redirections(argc, argv);
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
		else if(strcmp(argv[0],"myps")==0)
		{
		//	write_usr((myps),strlen("myps"));
			ps(history);
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
		
		else if(strcmp(argv[0],"myfree")==0)
		{
			myfree(argc,argv);
		}
		
		else if(strcmp(argv[0],"myuptime")==0)
		{
			myuptime();
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
	else if (strcmp(argv[1],"myps")==0)
		write_usr("myps : print last 10 processes\n",strlen("myps : print last 10 processes\n"));
	else if (strcmp(argv[1],"myfree")==0)
		write_usr("myfree : print RAM & SWAP information\n",strlen("myfree : print RAM & SWAP information\n"));
	else if (strcmp(argv[1],"myuptime")==0)
		write_usr("uptime : print the uptime for the system and the time spent in the idle process\n",strlen("uptime : print the uptime for the system and the time spent in the idle process\n"));
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




void ps (const process *history )
{
	int i  ;
	char* arr[] = {"1","2","3","4","5","6","7","8","9","10"};  
	char * carry = malloc (20);
	if (process_count==0)
		write_usr("no process yet \n",strlen("no process yet \n"));
	for ( i = 0 ; i < process_count && i < 10 ; i++ )
	{
		write_usr("process ",strlen("process "));
		write_usr(arr[i],strlen(arr[i]));
		write_usr("\n",strlen("\n"));
		
		sprintf(carry,"%d",history[i].PID);
		write_usr("ID: ",strlen("ID: "));
		write_usr( carry ,strlen( carry ) );
		write_usr("\n",strlen("\n"));
		
		write_usr("name: ",strlen("name: "));
		write_usr(history[i].name ,10 ) ;
		write_usr("\n",strlen("\n"));
		
		write_usr("exit status: ",strlen("exit status: "));
		write_usr(history[i].exit_status, strlen( history->exit_status) ) ;
		write_usr("\n",strlen("\n"));
	}
	free(carry);
}


void myfree (int argc , char ** argv)
{
	struct sysinfo info ;
	char * carry_1 = malloc (100);
	int error_state = sysinfo(&info);
	unsigned long  used_ram ;
	if(error_state == -1 )
	{
		perror("sysinfo");
		error_checker = 1 ;
		return  ;
	}
	unsigned long avaliable_ram = (info.freeram + info.bufferram +info.sharedram)  ;
	
	used_ram = (info.totalram - avaliable_ram ) ;
	
	write_usr("\tTotal\t\tused\t\tfree\t\tshared\tbuff/cache\tavailable\n", strlen("\t\tTotal\t\tused\t\tfree\t\tshared\tbuff/cache\tavailable\n") );
	write_usr("Mem:\t",strlen("Mem:\t"));
	sprintf(carry_1,"%ld\t\t%ld\t\t%ld\t\t%ld\t%ld\t\t%ld\n", info.totalram/(1024) , used_ram/(1024) , info.freeram/(1024)  , info.sharedram/(1024) , info.bufferram/(1024)  , avaliable_ram /(1024) );
	write_usr(carry_1,strlen(carry_1));
	
	free(carry_1);
	
	
	char * carry_2 = malloc (100);
	unsigned long int used_swap = info.totalswap - info.freeswap ;
	write_usr("Swap:\t",strlen("Swap:\t"));
	sprintf(carry_2,"%ld\t\t%ld\t\t%ld\n", info.totalswap/(1024) , used_swap/(1024) , info.freeswap/(1024) );
	write_usr(carry_2,strlen(carry_2));
	
	free(carry_2);
	
	
}

void myuptime (void) 
{

	struct sysinfo info ;
	char * carry_1 = malloc (100);
	int error_state = sysinfo(&info);
	if(error_state == -1 )
	{
		perror("sysinfo");
		error_checker = 1 ;
		return  ;
	}
	
	FILE * fd_idle = fopen("/proc/stat","r");
	
	
	
	
	unsigned long long user ,nice ,system,idle;
	fscanf(fd_idle,"cpu %llu %llu %llu %llu",&user,&nice,&system,&idle);
	
	unsigned long time = info.uptime ;
	unsigned long time_hour ;
	unsigned long time_min  ;
	unsigned long time_sec  ;
	
	time_hour = time / (60*60) ;
	time %= (60*60);
	time_min = time / 60 ;
	time %= (60);
	time_sec = time ;

	sprintf(carry_1,"%02ld:%02ld:%02ld\n",time_hour,time_min,time_sec);
	
	write_usr ("uptime for system : ",strlen("uptime for system : "));
	write_usr (carry_1,strlen(carry_1));
	
	free(carry_1);
	
	char * carry_2 = malloc (100);
	
	write_usr ("idle time : ",strlen("idle time : "));
	
	time = idle ;
	time_hour = time / (60*60) ;
	time %= (60*60);
	time_min = time / 60 ;
	time %= (60);
	time_sec = time ;
	
	sprintf(carry_2,"%lld\n",idle);
	
	write_usr (carry_2,strlen(carry_2));
	

}




