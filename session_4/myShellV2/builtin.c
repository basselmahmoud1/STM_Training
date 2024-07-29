#include "builtin.h"


void perform_builtin(int argc,char **argv)
{	
	if (argc != 0)
	{
		if(strcmp(argv[0],"pwd")==0)
		{
			write_usr("pwd is entered\n", strlen("pwd is entered\n") );
			//pwd ();
		}
		else if(strcmp(argv[0],"echo")==0)
		{
			write_usr("echo is entered\n", strlen("echo is entered\n") );
		//	echo ();
		}
		else if(strcmp(argv[0],"cp")==0)
		{
			//cp();
			write_usr("cp is entered\n", strlen("cp is entered\n") );
		}
		else if(strcmp(argv[0],"mv")==0)
		{
			write_usr("mv is entered\n", strlen("mv is entered\n") );
		//	mv();
		}
		else if(strcmp(argv[0],"exit")==0)
		{
			write_usr("exit is entered\n", strlen("exit is entered\n") );
			//exit_usr();
		}
		else if(strcmp(argv[0],"help")==0)
		{
			write_usr("help is entered\n", strlen("help is entered\n") );
			//help();
		}
		else
		{
			write_usr("command isnt supported\n", strlen("command isnt supported\n") );
		
		}
		
		
		
	}
	
	else 
		return ;

}




		
		
		
		
		
		
		
		
		
		
		
		
		
		
