#include <stdio.h>

#define MAX_PROCESSES 100  // Maximum number of processes

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void find_avg_time(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate waiting time and turnaround time
    proc[0].waiting_time = 0;  // Waiting time for the first process is 0

    for (i = 1; i < n; i++) {
	proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }

    for (i = 0; i < n; i++) {
	proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
	total_waiting_time += proc[i].waiting_time;
	total_turnaround_time += proc[i].turnaround_time;
    }

    // Print header with table format

    printf("| Process ID | Burst Time | Waiting Time   | Turnaround Time |\n");


    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void sort_processes(struct Process proc[], int n) {
    struct Process temp;
    // Sort processes by burst time using bubble sort
    for (i = 0; i < n - 1; i++) {
	for (j = 0; j < n - i - 1; j++) {
	    if (proc[j].burst_time > proc[j + 1].burst_time) {
		temp = proc[j];
		proc[j] = proc[j + 1];
		proc[j + 1] = temp;
	    }
	}
    }
}

int main() {
    int n,i;

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
    }

    sort_processes(proc, n);
    find_avg_time(proc, n);

    return 0;
}
