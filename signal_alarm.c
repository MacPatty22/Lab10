/*********************************************************************
* @file signal_alarm.c
* @brief schedules a SIGALRM for 5 seconds and handles it
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Set by the handler so main knows the alarm has fired
static volatile sig_atomic_t alarm_fired = 0;

void handle_alarm(int sig) {
    printf("Received SIGALRM (signal %d)\n", sig);
    alarm_fired = 1;
}

int main(void) {
    // Register the handler before scheduling the alarm
    signal(SIGALRM, handle_alarm);

    // Ask the OS to send SIGALRM in 5 seconds
    alarm(5);
    printf("Alarm scheduled for 5 seconds from now\n");

    // Count down each second until the alarm has been handled
    int remaining = 5;
    while (!alarm_fired) {
        if (remaining > 0) {
            printf("%d...\n", remaining);
            remaining--;
        }
        sleep(1);
    }
    return 0;
}