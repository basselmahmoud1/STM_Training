#include <unistd.h>
#include <stdio.h>


int main()
{
	char * arglist[]={NULL};
	char * envirlist[]={NULL};
	execvp("ls",arglist);

	printf("bassel");
}

