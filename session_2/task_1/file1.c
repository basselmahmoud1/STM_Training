#include <stdio.h>

int  global_var = 9 ;

extern void printing (void)
{
	printf("%d",global_var);
}
