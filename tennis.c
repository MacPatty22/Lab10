/*********************************************************************
* @file tennis.c
* @brief shared rally and scoring logic for signal tennis
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include "tennis.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Written by the signal handler and read by the game loop
static volatile sig_atomic_t signal_received = 0;
static volatile sig_atomic_t sender_pid = 0;
static volatile sig_atomic_t signal_value = 0;

static sigset_t wait_mask;      // Signal mask used while waiting for the ball
static int me = SERVER;         // SERVER or RECEIVER
static int points[2] = {0, 0};  // Points won, indexed by SERVER and RECEIVER

static void handle_ball(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    sender_pid = info->si_pid;
    signal_value = info->si_value.sival_int;
    signal_received = 1;
}

static void send_to_opponent(pid_t opponent, int data)
{
    // Clear the whole union, since sival_int only fills part of it
    union sigval value;
    memset(&value, 0, sizeof(value));
    value.sival_int = data;

    if (sigqueue(opponent, BALL_SIGNAL, value) == -1)
    {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }
}

static void format_score(char *text, size_t size)
{
    static const char *calls[] = {"Love", "15", "30", "40"};
    int server = points[SERVER];
    int receiver = points[RECEIVER];

    if (server >= 3 && receiver >= 3)
    {
        if (server == receiver)
        {
            snprintf(text, size, "Deuce");
        }
        else
        {
            snprintf(text, size, "Advantage %s",
                     server > receiver ? "Server" : "Receiver");
        }
    }
    else
    {
        snprintf(text, size, "Server %s - Receiver %s",
                 calls[server], calls[receiver]);
    }
}

static void award_point(int winner)
{
    char score[64];

    points[winner]++;

    if (game_over())
    {
        printf("Game: %s wins!\n", winner == SERVER ? "Server" : "Receiver");
    }
    else
    {
        format_score(score, sizeof(score));
        printf("Score: %s\n\n", score);
    }
}

void tennis_setup(int player)
{
    struct sigaction action;
    sigset_t ball_set;

    me = player;
    setvbuf(stdout, NULL, _IOLBF, 0);

    // Mixing in the PID gives each player a different random sequence
    srand((unsigned int)time(NULL) ^ (unsigned int)getpid());

    // Keep the signal blocked except while waiting, so none can be missed
    sigemptyset(&ball_set);
    sigaddset(&ball_set, BALL_SIGNAL);
    sigprocmask(SIG_BLOCK, &ball_set, &wait_mask);

    // Use the three argument handler, which requires SA_SIGINFO
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = handle_ball;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(BALL_SIGNAL, &action, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void random_wait(void)
{
    struct timespec delay;
    delay.tv_sec = 1;
    delay.tv_nsec = rand() % 1000000000L;
    nanosleep(&delay, NULL);
}

void hit_ball(pid_t opponent, int exchanges)
{
    printf("\aHitting the ball to PID %d (exchange %d)\n",
           opponent, exchanges);
    send_to_opponent(opponent, exchanges);
}

pid_t play_point(void)
{
    while (1)
    {
        // Wait for the other player
        while (!signal_received)
        {
            sigsuspend(&wait_mask);
        }

        pid_t opponent = sender_pid;
        int value = signal_value;
        signal_received = 0;

        // The opponent missed, so this player wins the point
        if (value == MISS_VALUE)
        {
            printf("The opponent missed the ball\n");
            award_point(me);
            return opponent;
        }

        printf("Received the ball from PID %d (exchange %d)\n",
               opponent, value);
        random_wait();

        // Missing ends the rally and gives the opponent the point
        if (value >= MAX_EXCHANGES || rand() % 100 < MISS_PERCENT)
        {
            printf("Missed the ball\n");
            send_to_opponent(opponent, MISS_VALUE);
            award_point(me == SERVER ? RECEIVER : SERVER);
            return opponent;
        }

        hit_ball(opponent, value + 1);
    }
}

int game_over(void)
{
    int difference = abs(points[SERVER] - points[RECEIVER]);

    return (points[SERVER] >= 4 || points[RECEIVER] >= 4) && difference >= 2;
}