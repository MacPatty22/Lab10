# Lab 10: Signals
Mac Patterson, CPE-2600

Programs that explore POSIX signals. Run make to build everything and
make clean to remove.

| Program | Description | How to run |
| --- | --- | --- |
| signal_handler | Handles SIGINT without exiting | ./signal_handler, stop it with kill -SIGKILL <pid> |
| signal_alarm | Handles a SIGALRM scheduled for 5 seconds later | ./signal_alarm |
| signal_segfault | Handles SIGSEGV and returns, so the fault repeats forever | ./signal_segfault, stop it with CTRL+C |
| signal_sigaction | Prints the PID that sent SIGUSR1 | ./signal_sigaction, then kill -SIGUSR1 <pid> |
| recv_signal | Prints the integer received with SIGUSR1 | ./recv_signal |
| send_signal | Sends SIGUSR1 with a random integer using sigqueue | ./send_signal <recv_signal pid> |
| tennis_recv | Receiving player for signal tennis | ./tennis_recv |
| tennis_serve | Serving player for signal tennis | ./tennis_serve <tennis_recv pid> |

Signal tennis uses traditional tennis scoring for one game. A player misses
20% of the time, and a rally ends on a miss once it reaches 10 exchanges. The
ball is the real time signal SIGRTMIN because pending real time signals queue
in order, and a value of -1 sent with the signal tells the other player that
the ball was missed.