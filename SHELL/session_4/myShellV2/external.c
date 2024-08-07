#include "external.h"

extern int error_checker ;

int process_count ;

process history [10] ;

void addProcessToHistory (pid_t CPID , char* p_name ,  int state ,char ** argv )
{
	char * carry ;
	if (state > 0)
	{
		carry = strdup("EXIT NORMALLY");
	}
	else if (state == 0)
	{
		carry = strdup("process EXIT ABNORMAL");
	}
	
	if (process_count < 10 )
	{
		history[process_count].name = strdup(p_name);
		history[process_count].PID = CPID;
		history[process_count].exit_status = carry ;
	}
	else
	{
		int i;
		for(i = 1 ; i < 10 ; i++ )
		{
			free(history[i-1].name);
			free(history[i-1].exit_status);
			history[i-1] = history [i] ;
		}
		history[9].name = strdup(p_name);
		history[9].PID = CPID;
		history[9].exit_status = carry ;
	}
	process_count ++ ;
}




void perform_EXT (int argc,char** argv)
{
	if (argc < 1 )
		return;
		
	pid_t CPID = fork();
	
	if (CPID > 0 )
	{
		int state ;
		CPID = wait(&state);
		if(CPID == -1 )
		{
			perror("waiting");
			error_checker = 1 ;
			return;
		}
		
		
		addProcessToHistory( CPID , argv[0] , WIFEXITED(state) ,argv);
					
	}
	
	else if (CPID == 0 )
	{
		int state = 0 ;
		
		state = execvp (argv[0],argv);
		
		if(state == -1 )
		{
			perror("execution");
			error_checker = 1 ;
			exit(0);
		}
		
		
	}
	else 
	{
		perror("fork");
		error_checker = 1 ;
		return;
	}
}
