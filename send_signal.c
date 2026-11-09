/*********************************************************************
* @file send_signal.c
* @brief sends SIGUSR1 with a random integer using sigqueue
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // The receiver's PID changes each run, so take it from the command line
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <receiver pid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t receiver = atoi(argv[1]);
    if (receiver <= 0)
    {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Seed the generator so each run sends a different number
    srand(time(NULL));

    // Clear the whole union, since sival_int only fills part of it
    union sigval value;
    memset(&value, 0, sizeof(value));
    value.sival_int = rand();

    printf("Sending value: %d\n", value.sival_int);

    if (sigqueue(receiver, SIGUSR1, value) == -1)
    {
        perror("sigqueue");
        return EXIT_FAILURE;
    }

    return 0;
}