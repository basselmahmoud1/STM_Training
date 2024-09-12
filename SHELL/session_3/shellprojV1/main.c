#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "functions.h"




int main()
{
	while(1)
	{
		//write promote msg
		write_usr( shellmsg , strlen(shellmsg) );
		// read input from the user 
		read_usr ();
		//perform command
		perform_comm(); 
	}
}
