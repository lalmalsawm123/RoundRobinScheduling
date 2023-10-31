#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

int generate_random_number(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void initialize_process(Process *process, int process_id, int arrival_time, int burst_time) {
    process->process_id = process_id;
    process->arrival_time = arrival_time;
    process->burst_time = burst_time;
    process->remaining_burst_time = burst_time;
    process->waiting_time = 0;
    process->turnaround_time = 0;
}

void round_robin_scheduling(Process *processes, int num_processes, int time_quantum) {
    int current_time = 0;

    while (1) {
        int done = 1;

        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                done = 0;

                if (processes[i].remaining_burst_time <= time_quantum) {
                    current_time += processes[i].remaining_burst_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_burst_time = 0;
                } else {
                    current_time += time_quantum;
                    processes[i].remaining_burst_time -= time_quantum;
                }
            }
        }

        if (done) {
            break;
        }
    }
}

void print_results(Process *processes, int num_processes) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    srand(time(NULL));

    int num_processes = 5;
    int time_quantum = 2;

    Process processes[num_processes];

    for (int i = 0; i < num_processes; i++) {
        initialize_process(&processes[i], i + 1, generate_random_number(0, 10),
                           generate_random_number(1, 10));
    }

    round_robin_scheduling(processes, num_processes, time_quantum);

    print_results(processes, num_processes);

    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= num_processes;
    avg_turnaround_time /= num_processes;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
