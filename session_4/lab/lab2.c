#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


int main ()
{
	char x ;
	x=getchar();
	char * argv[] = {"sp","100",NULL};
	
	execvp("sleep",argv);
	
}
