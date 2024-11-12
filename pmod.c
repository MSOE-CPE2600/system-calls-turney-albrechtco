// Connor Albrecht
// Lab 9
// CPE 2600 121
// pmod.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // Reduce priority by 10
    int current_priority = getpriority(PRIO_PROCESS, 0);
    if (setpriority(PRIO_PROCESS, 0, current_priority + 10) != 0) {
        perror("Failed to reduce priority");
        return EXIT_FAILURE;
    }
    printf("Priority reduced by 10\n");

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec ts = {1, 837272638};
    if (nanosleep(&ts, NULL) != 0) {
        perror("Failed to sleep");
        return EXIT_FAILURE;
    }

    // Print goodbye message
    printf("Goodbye\n");
    return EXIT_SUCCESS;
}
