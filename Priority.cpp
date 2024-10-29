#include <stdio.h>
#include <conio.h>
#define MAX_PROCESSES 100  // Maximum number of processes

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int priority;
};

void find_avg_time(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes by priority (lower number indicates higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    proc[0].waiting_time = 0;  // Waiting time for the first process is 0
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }

    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    // Print results
    printf("\n+------------+------------+---------------+-----------------+------------+\n");
    printf("| Process ID | Burst Time | Waiting Time   | Turnaround Time | Priority   |\n");
    printf("+------------+------------+---------------+-----------------+------------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %-10d | %-10d | %-13d | %-15d | %-10d |\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time, proc[i].priority);
    }
    
    printf("+------------+------------+---------------+-----------------+------------+\n");
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
clrscr();
    int n;

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
        printf("Enter priority for process %d (lower number indicates higher priority): ", proc[i].id);
        scanf("%d", &proc[i].priority);
    }

    find_avg_time(proc, n);
    getch();	
    return 0;
}
