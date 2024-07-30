#include "functions.h"



int error_checker = 0;
int argc ;
char ** argv ;
char  command[COMM_SIZE];

const char *shellmsg ="engez mafesh w2t lel tafser $> ";


void read_usr (void)
{
    ssize_t readsize = 0;
    readsize = read (STDIN,command,COMM_SIZE);

    if (readsize == -1)
    {
        perror("read:");
        error_checker = 1;
    }

        command [readsize-1]='\0';



}

int get_tokens_num (const char * buff )
{
    char cp [COMM_SIZE] ;
    strcpy(cp,buff);
    int counter=0;
    char *tokens = strtok( cp , " " );
    while (tokens != NULL )
    {
        counter++;
        tokens = strtok( NULL , " " );
    }
    return counter;
}

char ** get_tokens (const char * buff )
{
    if (argc == 0)
        return NULL ;
    int counter =0;
    char cp [COMM_SIZE] ;
    char ** argg;

    strcpy(cp,buff);

    argg = malloc((argc+1) * sizeof(char*)) ;
    if (argg == NULL) {
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

    argg[counter] = NULL ;
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


int type (int argc ,char ** argv)
{
	if (argc < 1)
		return 3 ;
	char * supp_comm [] = {"cd","mycp","echo","exit","help","mymv","mypwd","type","envir",NULL} ;
	int counter ;
	for(counter = 0 ; supp_comm[counter] != NULL ; counter++ )
	{
		if(strcmp(supp_comm[counter],argv[0])==0)
			return INTERNAL;
	}

	// a3mel tokens w e3mel strcat leeh esm el program m3 kol token weeh cheak lw kan mogood wala laa
	char * path = getenv("PATH");
	char * path_cpy = strdup(path);
	char * token = strtok(path_cpy,":");
	char * modified_path =token ;
	struct stat st ;
	while (token != NULL)
	{
		strcpy (modified_path,token);
		strcat (modified_path,"/");
		strcat	(modified_path,argv[0]);

		int x = stat(token,&st);
		if((st.st_mode & S_IXUSR) && (x == 0 ) )
		{
			free (path);
			return EXTERNAL ;
		}

		token = strtok(NULL,":");

	}
	free (path);

	return UN_SUPP ;







}
