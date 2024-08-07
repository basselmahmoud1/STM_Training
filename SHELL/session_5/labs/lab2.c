#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void redirect (int fdnew , const int fdold);

int main (int argc , char ** argv )
{
        char  buff[100] ;
	int fd_e = open("error",O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
	int fd_o = open("out",O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
	/*printf("%d\n",fd_e);
	printf("%d\n",fd_o);*/
	
	redirect(2 ,fd_e);
	redirect(1,fd_o);	
	
	printf("bassel\n");
        ssize_t i = readlink("/proc/self/fd/0",buff , 100);
        printf("%s\n",buff);
        //strcpy()
        readlink("/proc/self/fd/1",buff , 100);
        printf("%s\n",buff);
        readlink("/proc/self/fd/2",buff , 100);
        printf("%s\n",buff);
        int fd_b = open("bassel",O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);
        
	execvp("sleep",argv);

        readlink("/proc/self/fd/3",buff , 100);
                printf("%s\n",buff);
}

void redirect (int fdnew ,  int fdold)
{
	dup2(fdold,fdnew);
	close (fdold);
}
