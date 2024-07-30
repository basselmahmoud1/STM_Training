#include "builtin.h"


void perform_builtin(int argc,char **argv)
{
	if (argc != 0)
	{
		if(strcmp(argv[0],"pwd")==0)
		{
			pwd (argc,argv);
		}
		else if(strcmp(argv[0],"echo")==0)
		{
			echo (argc,argv);
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
			help(argc,argv);
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
	else if (strcmp(argv[1],"cp")==0)
		write_usr("cp : copy a file given (1st argumment) into the other file (2nd argumment)\n",strlen("cp : 					copy a file given (1st argumment) into the other file (2nd argumment)\n"));
	else if (strcmp(argv[1],"echo")==0)
		write_usr("echo : print back the string given\n",strlen("echo : print back the string given\n"));
	else if (strcmp(argv[1],"pwd")==0)
		write_usr("pwd : prints the current working directory\n",strlen("pwd : prints the current working directory\n"));
	else if (strcmp(argv[1],"mv")==0)
		write_usr("mv : move file to another directory\n",strlen("mv : move file to another directory\n"));
	else if (strcmp(argv[1],"exit")==0)
		write_usr("exit : terminates the shell\n",strlen("exit : terminates the shell\n"));
	else if (strcmp(argv[1],"help")==0)
		write_usr("supported builtin commands are:\nhelp\nexit\nmv\npwd\necho\ncp\n",strlen("supported builtin commands are:\nhelp\nexit\nmv\npwd\necho\ncp\n"));
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


void pwd (int argc ,char **argv )
{

	char *error_state;
	char CWD [PATH_MAX];
	error_state = getcwd ( CWD , PATH_MAX );

	if(error_state == NULL)
	{
		perror("pwd:");
		error_checker = 1 ;
	}

	//write_usr("\n", strlen("\n") );
	write_usr( CWD , strlen(CWD) ) ;
	write_usr("\n", strlen("\n") );
}
