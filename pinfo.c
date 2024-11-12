// Connor Albrecht
// Lab 9
// CPE 2600 121
// info.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>  


void print_scheduler(int scheduler) {
    switch (scheduler) {
        case SCHED_OTHER:
            printf("Scheduling Method: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling Method: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling Method: SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("Scheduling Method: SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("Scheduling Method: SCHED_IDLE\n");
            break;
        case SCHED_DEADLINE:
            printf("Scheduling Method: SCHED_DEADLINE\n");
            break;
        default:
            printf("Unknown Scheduling Method\n");
    }
}

int main(int argc, char *argv[]) {
    pid_t pid = (argc > 1) ? atoi(argv[1]) : getpid();

    // Check if the process exists
    if (kill(pid, 0) != 0 && errno == ESRCH) {
        fprintf(stderr, "Error: Process with PID %d does not exist.\n", pid);
        return EXIT_FAILURE;
    }

    // Get process priority
    int priority = getpriority(PRIO_PROCESS, pid);
    printf("Process Priority: %d\n", priority);

    // Get scheduling method
    int scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        perror("Failed to get scheduling method");
        return EXIT_FAILURE;
    }
    print_scheduler(scheduler);

    return EXIT_SUCCESS;
}
