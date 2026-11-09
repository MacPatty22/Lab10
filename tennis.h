/*********************************************************************
* @file tennis.h
* @brief shared declarations for signal tennis
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#ifndef TENNIS_H
#define TENNIS_H
#include <signal.h>
#include <sys/types.h>
#define SERVER 0
#define RECEIVER 1
#define BALL_SIGNAL SIGRTMIN
#define MISS_VALUE -1        // Sent instead of the exchange count on a miss
#define MAX_EXCHANGES 10     // A rally ends on a miss at this many exchanges
#define MISS_PERCENT 20      // Chance of failing to return the ball

void tennis_setup(int player);
void random_wait(void);
void hit_ball(pid_t opponent, int exchanges);
pid_t play_point(void);
int game_over(void);

#endif