#include "coordinator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *agent_names[] = {"Gamma", "Beta", "Alpha", "Delta"};

void create_agents() {
    for (int i = 0; i < 4; i++) {
        int fd[2];
        pipe(fd);
        pid_t pid = fork();
        if (pid == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);              
            execl("./agent", "agent", agent_names[i], NULL);
            perror("execl");
            exit(1);
        } else {
            close(fd[0]);
            write(fd[1], "Identify!\n", 10);
            write(fd[1], "Status?\n", 8);
            close(fd[1]);
        }
    }

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }
}

