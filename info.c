// Connor Albrecht
// Lab 9
// CPE 2600 121
// info.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void print_current_time() {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        printf("Current time: %ld nanoseconds\n", ts.tv_nsec);
    } else {
        perror("Failed to get current time");
    }
}

void print_network_name() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Network name: %s\n", hostname);
    } else {
        perror("Failed to get network name");
    }
}

void print_system_info() {
    struct utsname uname_data;
    if (uname(&uname_data) == 0) {
        if (strlen(uname_data.sysname) > 0)
            printf("Operating System: %s\n", uname_data.sysname);
        if (strlen(uname_data.release) > 0)
            printf("OS Release: %s\n", uname_data.release);
        if (strlen(uname_data.version) > 0)
            printf("OS Version: %s\n", uname_data.version);
        if (strlen(uname_data.machine) > 0)
            printf("Hardware Type: %s\n", uname_data.machine);
    } else {
        perror("Failed to get system information");
    }
}

void print_cpu_count() {
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs > 0) {
        printf("Number of CPUs: %ld\n", nprocs);
    } else {
        perror("Failed to get number of CPUs");
    }
}

void print_memory_info() {
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) == 0) {
        printf("Total physical memory: %lu bytes\n", sys_info.totalram * sys_info.mem_unit);
        printf("Free memory: %lu bytes\n", sys_info.freeram * sys_info.mem_unit);
    } else {
        perror("Failed to get memory information");
    }
}

int main(int argc, char* argv[]) {
    print_current_time();
    print_network_name();
    print_system_info();
    print_cpu_count();
    print_memory_info();
    return 0;
}
