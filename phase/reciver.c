
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>

    #include <unistd.h>

void handler(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGRTMIN)
    {
        printf("data recived: %d\n", info->si_value.sival_int);
        int x = info->si_value.sival_int;
        if (x == 0)
        {
            printf("terminated\n");
            exit(0);
        }
        else if (x == 1)
        {
            printf("generate core dump and closing\n");
            abort();
        }
        else
        {
            printf("unknown data\n");
        }
    }
}

int main()
{
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;  // 3lshan a3mle access lel data
    if (sigaction(SIGRTMIN, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Waiting \n");

    
    pause();
    

}
