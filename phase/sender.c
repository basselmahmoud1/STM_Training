
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int receiver_pid = atoi(argv[1]);
    int data = atoi(argv[2]);

    if (data != 0 && data != 1) {
        printf("invalid input\n");
        return 1;
    }

    union sigval senddata;
    senddata.sival_int = data;
    if (sigqueue(receiver_pid, SIGRTMIN, senddata) == -1) {
        perror("sigqueue");
        return 1;
    }
    printf("signal sent successfully\n");
    
}
