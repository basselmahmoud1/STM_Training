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






void perform_EXT (int argc,char** argv,operant op , int loc)
{
	if (argc < 1 )
		return;
	
	redirections(argc, argv);
	
	if(op == pipe_p)
	{
		argv[loc] = NULL ; 
		
		char ** argv1 = argv ; 
		char ** argv2 = &argv[loc+1] ;
		
		int filedes[2];
		
		int error = pipe (filedes);
		if(error == -1)
		{
			perror("pipe:");
			error_checker=1;
			return;
		}
		pid_t CHILD1 = fork();
		
		
		if (CHILD1 == -1 )
		{
			perror("CHILD1:");
			error_checker=1;
			return;	
		}
		
		if ( CHILD1 == 0 ) 
		{
			close (filedes[0]);
			dup2 (filedes[1],STDOUT);
			close (filedes[1]);
			execvp(argv1[0] , argv1);
			perror ("execution 1 : ");
			return ; 
		}
		else 
		{
			pid_t CHILD2 = fork();
			if (CHILD2 == -1 )
			{
				perror("CHILD2");
				error_checker=1;
				return;	
			}
			if(CHILD2 == 0)
			{
				close (filedes[1]);
				dup2 (filedes[0],STDIN);
				close (filedes[0]);
				execvp (argv2[0],argv2);
				perror ("execution 2 : ");
				return ;
			}
			else		// parent process
			{	
				close (filedes[0]);
				close (filedes[1]);
				int state = 0 ;
				waitpid(CHILD1,&state,0);
				addProcessToHistory(CHILD1 , argv1[0] , WIFEXITED(state) ,argv1);
				state = 0 ;
				waitpid(CHILD2,&state,0);
				addProcessToHistory(CHILD2 , argv2[0] , WIFEXITED(state) ,argv2);
				
			}	
		}
	
	}

	else 
	{	
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
}
