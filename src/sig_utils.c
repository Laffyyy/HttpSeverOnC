#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifdef _WIN32
    #include <io.h>
    #include <process.h>
#else
    #include <sys/signal.h>
    #include <sys/wait.h>
    #include <unistd.h>
#endif

#include "sig_utils.h"

void sigchld_handler() {
#ifndef _WIN32
    // Automatically reap all exited child processes on Linux
    while (waitpid(-1, NULL, WNOHANG) > 0);
#endif
}

void signal_handler(int signum) {
    switch (signum) {
#ifndef _WIN32
        case SIGCHLD:
            sigchld_handler();
            break;
#endif
        case SIGTERM:
        case SIGINT:
            break;
    }
}

int init_signal_handler() {
#ifndef _WIN32
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("Error setting up SIGCHLD handler");
        return -1;
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Error setting up SIGTERM handler");
        return -1;
    }
#else
    // Windows fallback using basic signal()
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
#endif
    return 0;
}