#include "functions.h"



int error_checker = 0; //variable used to check if systemcall is succesful or not
int argc ; // no of arguments entered by user
char ** argv ; // array carring arguments passed by user
char  command[COMM_SIZE]; // buffer to store command

const char *shellmsg ="\033[1;36mEngez Mafesh W2t Lel Tafser $> \033[m"; // colored promote massage


void read_usr (void)
{
    ssize_t readsize = 0; // no of data read by syscall read
    readsize = read (STDIN,command,COMM_SIZE); // reading command from User (STDIN)

    if (readsize == -1) //error checking
    {
        perror("read:");
        error_checker = 1;
    }

        command [readsize-1]='\0'; //concatinating the NULL char to command



}

int get_tokens_num (const char * buff )
{
    char cp [COMM_SIZE] ; // carrier for command
    strcpy(cp,buff); // copying command to carrier buffer 
    int counter=0; 
    char *tokens =  strtok( cp , " " ); // tokenizing command every space
    while (tokens != NULL )
    {
        counter++; // calculating no of tokens 
        tokens = strtok( NULL , " " ); //tokenize the next token
    }
    return counter; // no of argumnets
}

char ** get_tokens (const char * buff )
{
    if (argc == 0) //checking if user entered Enter
        return NULL ; 
    int counter =0; 
    char cp [COMM_SIZE] ;
    char ** argg; // array of strings to carry arguments 

    strcpy(cp,buff);

    argg = malloc((argc+1) * sizeof(char*)) ; //freeing space for argg to store correctly
    if (argg == NULL) { //checking error
        perror("malloc");
        argc=0;
        return NULL ;
    }


    char *token  = strtok( cp , " " ); 
    while (token != NULL )
    {
        argg[counter] = strdup(token);
        token = strtok( NULL , " " );
        counter++;
    }

    argg[counter] = NULL ; //terminating the argg by NULL terminator
    return argg;

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


int type (int argc ,char * argss)
{
	if (argc < 1)    // error checking
		return 3 ;
	char * supp_comm [] = {"cd","mycp","echo","exit","help","mymv","mypwd","type","envir","myps","myfree","myuptime",NULL} ; // array carring supported commands 
	int counter ;
	for(counter = 0 ; supp_comm[counter] != NULL ; counter++ )  //iterating over supported commands 
	{
		if(strcmp(supp_comm[counter],argss)==0)  //checking if the command entered by user is a supported command or not
			return INTERNAL; // macro to define the return type
	}
	
	char * path = getenv("PATH");  //getting value of envirnoment variable "PATH" to check External commands in it
	char * path_cpy = strdup(path); // make a copy of path to work on it 
	char * token = strtok(path_cpy,":");  // tokenizing PATH every ":"
	char  modified_path [PATH_MAX]  ;
	struct stat st ;
	while (token != NULL)
	{
		strcpy (modified_path,token);
		strcat (modified_path,"/");
		strcat	(modified_path,argss);


		if((stat(modified_path,&st) == 0 ) && (st.st_mode & S_IXUSR)   )
		{
			free (path_cpy);
			return EXTERNAL ;
		}

		token = strtok(NULL,":");

	}
	free (path_cpy);

	return UN_SUPP ;

}





void redirections (int argc , char ** argv )
{
	int i , fd_out , fd_in ,fd_err ,fd_both;
	for( i = 0 ; i < argc ; i++)
	{
		if( strcmp(argv[i],">") == 0 )
		{
			fd_out = open (argv[i+1] , O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR | S_IWUSR);
			if (fd_out == -1 )
			{
				perror("fd_out:");
				error_checker=1;
				return;
			}
			dup2(fd_out,STDOUT);
			close (fd_out);
			argv[i] = '\0';
		}
		
		else if (strcmp(argv[i],"<") == 0)
		{
			fd_in = open (argv[i+1] , O_RDONLY );
			if (fd_in == -1 )
			{
				perror("fd_in:");
				error_checker=1;
				return;
			}
			dup2(fd_in,STDIN);
			close (fd_in);
			argv[i] = '\0';
		
		}
		
		else if (strcmp(argv[i],"2>") == 0)
		{
			fd_err = open (argv[i+1] ,O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR | S_IWUSR );
			if (fd_err == -1 )
			{
				perror("fd_err:");
				error_checker=1;
				return;
			}
			dup2(fd_err,STDERR);
			close (fd_err);
			argv[i] = '\0';
		}
	
		else if ( strcmp(argv[i],"2>&1") == 0 )
		{
			dup2 (STDOUT , STDERR);
			argv[i] = '\0';
		}
		
	
	
	
	}	
}

void env_var ( int argc , char ** argv,int loc )
{
	int len = strlen(argv[loc]);
	int i ;
	char *arr ;
	arr = strdup(argv[loc]);
	
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



void set_env_var(int argc,char ** argv)
{
	int error = setenv(argv[0],argv[2],1);
	if (error == -1)
	{
		perror("setenv :");
		error_checker=1;
		return;
	}
	
}




