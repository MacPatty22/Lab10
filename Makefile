CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = signal_handler signal_alarm signal_segfault signal_sigaction \
           recv_signal send_signal tennis_recv tennis_serve

all: $(PROGRAMS)

signal_handler: signal_handler.c
	$(CC) $(CFLAGS) -o $@ $<

signal_alarm: signal_alarm.c
	$(CC) $(CFLAGS) -o $@ $<

signal_segfault: signal_segfault.c
	$(CC) $(CFLAGS) -o $@ $<

signal_sigaction: signal_sigaction.c
	$(CC) $(CFLAGS) -o $@ $<

recv_signal: recv_signal.c
	$(CC) $(CFLAGS) -o $@ $<

send_signal: send_signal.c
	$(CC) $(CFLAGS) -o $@ $<

tennis_recv: tennis_recv.c tennis.c tennis.h
	$(CC) $(CFLAGS) -o $@ tennis_recv.c tennis.c

tennis_serve: tennis_serve.c tennis.c tennis.h
	$(CC) $(CFLAGS) -o $@ tennis_serve.c tennis.c

clean:
	rm -f $(PROGRAMS)

.PHONY: all clean