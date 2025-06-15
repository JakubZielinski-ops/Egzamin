CC=gcc
CFLAGS=-Wall -g

all: coordinator agent main

coordinator: coordinator.c
	$(CC) $(CFLAGS) -c coordinator.c

agent: agent.c
	$(CC) $(CFLAGS) -o agent agent.c

main: main.c coordinator.o
	$(CC) $(CFLAGS) -o koordynator main.c coordinator.o

clean:
	rm -f *.o koordynator agent

