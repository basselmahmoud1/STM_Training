#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main (int argc , char ** argv )
{
	char  buff[100] ;
	ssize_t i = readlink("/proc/self/fd/0",buff , 100);
	printf("%s\n",buff);
	//strcpy()
	readlink("/proc/self/fd/1",buff , 100);
	printf("%s\n",buff);
	readlink("/proc/self/fd/2",buff , 100);
	printf("%s\n",buff);
	int fd_b = open("bassel",O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);
	char arr[100] ="/proc/self/fd/";
	
	readlink("/proc/self/fd/3",buff , 100);
		printf("%s\n",buff);
}
