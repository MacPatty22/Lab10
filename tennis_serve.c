/*********************************************************************
* @file tennis_serve.c
* @brief Lab 10 Signals - serving player for signal tennis
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include "tennis.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver pid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t opponent = atoi(argv[1]);
    if (opponent <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    tennis_setup(SERVER);

    // The server serves again after every point
    while (!game_over()) {
        hit_ball(opponent, 1);
        opponent = play_point();

        if (!game_over()) {
            random_wait();
        }
    }
    return 0;
}