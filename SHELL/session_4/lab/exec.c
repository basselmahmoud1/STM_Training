#include <unistd.h>
#include <stdio.h>


int main()
{
	char * arglist[]={NULL};
	char * envirlist[]={NULL};
	execve ("/usr/bin/ls",arglist,envirlist);

	printf("bassel");
}

