#include "agent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

char agent_name[50];

void sigusr1_handler(int sig) {
    printf("%s: Czekam na rozkazy\n", agent_name);
    fflush(stdout);
}

void sigusr2_handler(int sig) {
    printf("%s: Rozpoczynam misję\n", agent_name);
    fflush(stdout);
}

void sigterm_handler(int sig) {
    printf("%s: Misja zakończona\n", agent_name);
    fflush(stdout);
    exit(0);
}

void handle_agent(const char *name) {
    strcpy(agent_name, name);
    printf("%s: Gotowy do misji\n", agent_name);
    fflush(stdout);

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
    signal(SIGTERM, sigterm_handler);

    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "Identify", 8) == 0) {
            printf("My codename is %s\n", agent_name);
        } else if (strncmp(line, "Status", 6) == 0) {
            printf("%s: My PID is: %d\n", agent_name, getpid());
        }
        fflush(stdout);
    }

    pause();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <nazwa_agenta>\n", argv[0]);
        return 1;
    }
    handle_agent(argv[1]);
    return 0;
}

