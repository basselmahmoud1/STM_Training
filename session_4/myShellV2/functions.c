#include "functions.h"


int  counter;
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
    argg = malloc(argc * sizeof(char*)) ;
    char *token  = strtok( cp , " " );
    while (token != NULL )
    {
        argg[counter] = strdup(token);
        token = strtok( NULL , " " );
        counter++;
    }
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
