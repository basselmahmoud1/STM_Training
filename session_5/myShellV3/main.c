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

        write_usr(shellmsg,strlen(shellmsg)); //write promote message 
        read_usr();	// read input from user
        argc = get_tokens_num(command); // saving number of argumments entered by user
        argv = get_tokens(command); // saving argumments entered by user
        if (argc == 0) //checking if user entered "ENTER" 
        	continue ;
        	
        if (argv[0][0]=='$') //checking if user entered a environment variable
        {
        	env_var(argc,argv); //dereferencing environment variable
        	continue;
        }
        
      
        
        for ( i = 0 ; i < argc ; i++ )
        {
        	
        	if( strcmp(argv[i],"|") == 0)
        	{
        		loc = i ;
        		op = pipe_p;
        	}
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

    }
}
