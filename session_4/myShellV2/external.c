#include "external.h"

extern int error_checker ;

int process_count ;

extern process history[10] ;

void addProcessToHistory (pid_t CPID , char* p_name ,  int state ,char ** argv )
{
	char * carry ;
	if (state > 0)
	{
		carry = "EXIT NORMALLY";
	}
	else if (state == 0)
	{
		carry = "process EXIT ABNORMAL";
	}
	
	if (process_count < 10 )
	{
		history[process_count].name = argv[0];
		history[process_count].PID = CPID;
		history[process_count].exit_status = carry ;
	}
	else
	{
		int i;
		for(i = 1 ; i < 10 ; i++ )
			history[i-1] = history [i] ;
		history[9].name = argv[0];
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
			return;
		}
		
	}
	else 
	{
		perror("fork");
		error_checker = 1 ;
		return;
	}
}
