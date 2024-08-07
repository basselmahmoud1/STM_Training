#include <stdio.h>
#include "builtin.h"
#include "functions.h"
#include "external.h"


extern char command [1001];
extern char ** argv;
extern int argc ;


int main(void) {

    while(1) { //super loop 

        int i =0 , loc=0 ; // initializing counter
        operant op = noop;
        int stdin  = dup(STDIN); 
        int stdout = dup(STDOUT);
        int stderr = dup(STDERR);
        

        write_usr(shellmsg,strlen(shellmsg)); //write promote message 
        read_usr();	// read input from user
        argc = get_tokens_num(command); // saving number of argumments entered by user
        argv = get_tokens(command); // saving argumments entered by user
        if (argc == 0) //checking if user entered "ENTER" 
        	continue ;
        	
        
        
      
        
        for ( i = 0 ; i < argc ; i++ )
        {
        	
        	if( strcmp(argv[i],"|") == 0)
        	{
        		loc = i ;
        		op = pipe_p;
        	}
        	if (strcmp(argv[i] , "=") == 0 )
        	{
        		op = envir_var;
        		
        	}
        	if (argv[i][0]=='$') //checking if user entered a environment variable
       		{
       			op = deref;
       		 	env_var(argc,argv,i); //dereferencing environment variable
       		 	if (i == 0 )
       		 		break;
        	}
  
        	
        }

        if (op== deref )     
        	 continue;
        if (op == envir_var )
        {
        	set_env_var(argc,argv);
        	continue ;
        } 
        
        switch (type(argc,argv[0])) // checking type of command entered by user
        {
      		case EXTERNAL :	perform_EXT(argc,argv,op,loc); 	break;  // perform the external command
        
        	case INTERNAL :	perform_builtin(argc,argv,op,loc);	break;// perform the Internal built in command
        
        	case UN_SUPP : write_usr("unsupported command\n",strlen("unsupported command\n")); // command not found
        }
        
        for(i=0 ; i<argc && argv[i] != NULL ; i++)
            free (argv[i]); // freeing space to use argv in the next command
        free (argv);
        dup2(stdin,STDIN);
        dup2(stdout,STDOUT);
        dup2(stderr,STDERR);
        
       	close(stdin);
       	close(stderr);
       	close(stdout);

    }
}
