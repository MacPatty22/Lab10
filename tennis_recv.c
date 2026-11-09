/*********************************************************************
* @file tennis_recv.c
* @brief receiving player for signal tennis
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include "tennis.h"
#include <stdio.h>
#include <unistd.h>

int main(void) {
    tennis_setup(RECEIVER);
    printf("Receiver ready. Run: ./tennis_serve %d\n", getpid());

    // The signal handler finds the server's PID when the first ball arrives
    while (!game_over()) {
        play_point();
    }
    return 0;
}