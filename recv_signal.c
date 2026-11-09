/*********************************************************************
* @file recv_signal.c
* @brief receives SIGUSR1 and prints the integer sent with it
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_usr1(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    printf("Received value: %d\n", info->si_value.sival_int);
}

int main(void)
{
    struct sigaction action;

    // Use the three argument handler, which requires SA_SIGINFO
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = handle_usr1;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGUSR1, &action, NULL) == -1)
    {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("My PID is %d\n", getpid());
    while (1)
    {
        sleep(1);
    }
    return 0;
}