#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

int loop_size = 10000;
int large_interval = 10e2;
int large_size = 30;
int freq_interval = 30;
int freq_size = 5;
// int pid;

void env(int size, int interval, char* env_name) {
    int loop_len = 10e5;
    int fork_n = size;
    printf("Running %s:\n", env_name);
    for (int i = 0; i < loop_len; i++) {
        if (i % interval == 0) {
            int pid = fork();
            if (pid == 0) {
                for(int j = 0; j < fork_n; j++) {
                    int calculation = interval * interval * interval * interval * interval * interval * interval;
                    calculation++;
                    fork();
                }
                exit(0);
            }
            else wait(&pid);
        } else if(i == loop_len / 2) pause_system(5);
    }
    exit(0);
}

void env_large() {
    int pid = fork();
    if(pid == 0) env(large_size, large_interval, "env_large");
    else wait(&pid);
}

void env_freq() {
    int pid = fork();
    if(pid == 0) env(freq_size, freq_interval, "env_freq");
    else wait(&pid);
}

int
main(int argc, char *argv[])
{
    // int n_forks = 2;
    // int pid = getpid();
    // for (int i = 0; i < n_forks; i++) {
    //     fork();
    // }
    // // int larges = 0;
    // // int freqs = 0;
    // int n_experiments = 10;
    // for (int i = 0; i < n_experiments; i++) {
    //     env_large(10, 3, 100);
    //     if (pid == getpid()) {
    //         printf("experiment %d/%d\n", i + 1, n_experiments);
    //         // larges = (larges * i + get_utilization()) / (i + 1);
    //     }
    //     sleep(10);
    //     env_freq(10, 100);
    //     if (pid == getpid()) {
    //         // freqs = (freqs * i + get_utilization()) / (i + 1);
    //     }
    // }
    // if (pid == getpid()) {
    //     // printf("larges = %d\nfreqs = %d\n", larges, freqs);
    //     print_stats();
    // }
    print_stats();
    env_freq();
    print_stats();
    env_large();
    print_stats();
    exit(0);
}
