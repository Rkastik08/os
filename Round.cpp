#include <stdio.h>
#include <conio.h>
#define MAX_PROCESSES 100  // Maximum number of processes

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;  // Remaining time for Round Robin
};

void find_avg_time(struct Process proc[], int n, int quantum) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int time = 0;
    int remaining_processes = n;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time;
                    total_waiting_time += proc[i].waiting_time;
                    total_turnaround_time += proc[i].turnaround_time;
                    proc[i].remaining_time = 0;
                    remaining_processes--;
                }
            }
        }
    }

    // Print results
    printf("\n+------------+------------+---------------+-----------------+\n");
    printf("| Process ID | Burst Time | Waiting Time   | Turnaround Time |\n");
    printf("+------------+------------+---------------+-----------------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %-10d | %-10d | %-13d | %-15d |\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
    
    printf("+------------+------------+---------------+-----------------+\n");
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
clrscr();
    int n, quantum;

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n > MAX_PROCESSES) {
        printf("Error: Number of processes exceeds maximum limit.\n");
        return 1;
    }

    struct Process proc[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;  // Assign process IDs
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;  // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    find_avg_time(proc, n, quantum);
    getch();	
    return 0;
}
