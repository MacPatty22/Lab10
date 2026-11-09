/*********************************************************************
* @file signal_handler.c
* @brief registers a SIGINT handler that does not exit
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig) {
    (void)sig;
    printf("Received a signal\n");
}

int main(void) {
    // Register the handler for SIGINT
    signal(SIGINT, handle_signal);

    printf("My PID is %d\n", getpid());

    // Wait forever
    while (1) {
        printf("Sleeping\n");
        sleep(1);
    }
    return 0;
}