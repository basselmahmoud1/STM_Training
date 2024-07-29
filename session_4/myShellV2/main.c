#include <stdio.h>

#include "functions.h"
extern char command [1001];
extern char ** argv;
extern int argc ;
int main(void) {
    while(1) {
        write_usr(shellmsg,strlen(shellmsg));
        read_usr();
        argc = get_tokens_num(command);
        argv = get_tokens(command);
        
        // check if it is  external
        //  check if builtin function
        perform_builtin(argc,argv);
        // nethier generate un supported func
        
        
        
        for(i=0 ; i<argc && argv[i] != NULL ; i++)
            free (argv[i]);
        free (argv);

    }
}
