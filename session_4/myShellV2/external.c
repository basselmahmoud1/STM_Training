#include "external.h"

extern int error_checker ;

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
