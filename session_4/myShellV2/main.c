#include <stdio.h>
#include "builtin.h"
#include "functions.h"
#include "external.h"


extern char command [1001];
extern char ** argv;
extern int argc ;


int main(void) {

    while(1) {

        write_usr(shellmsg,strlen(shellmsg));
        read_usr();
        argc = get_tokens_num(command);
        argv = get_tokens(command);
        if (argc == 0)
        	continue ;
        if (argv[0][0]=='$')
        {
        	env_var(argc,argv);
        	continue;
        }
        switch (type(argc,argv[0]))
        {
      		case EXTERNAL :	perform_EXT(argc,argv); 	break;
        
        	case INTERNAL :	perform_builtin(argc,argv);	break;
        
        	case UN_SUPP : write_usr("unsupported command\n",strlen("unsupported command\n"));
        }
        
        int i =0 ;
        for(i=0 ; i<argc && argv[i] != NULL ; i++)
            free (argv[i]);
        free (argv);

    }
}
