#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


int main ()
{
	int childID =fork();

	if (childID>0)
	{
		printf("PARENT\n");
		while (1);
	}
	else if (childID == 0 )
	{
		printf("CHILD\n");
		while(1);
	}
	else 
	{
		perror("fork:");
	}
}
