#include <stdio.h>
#include <conio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int num_processes, num_resources;

void calculate_need() {
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0}; // 0 means not finished, 1 means finished
    int count = 0;

    // Initialize work with available resources
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];

    while (count < num_processes) {
        int found = 0;
        for (int p = 0; p < num_processes; p++) {
            // Check if this process can finish
            int can_finish = 1; // Assume it can finish
            for (int j = 0; j < num_resources; j++) {
                if (need[p][j] > work[j]) {
                    can_finish = 0; // It cannot finish
                    break;
                }
            }

            // If it can finish, simulate the allocation
            if (can_finish && !finish[p]) {
                for (int j = 0; j < num_resources; j++)
                    work[j] += allocation[p][j]; // Release allocated resources
                finish[p] = 1; // Mark this process as finished
                found = 1; // Found a process that can finish
                count++;
            }
        }

        // If no process could finish, return false
        if (!found)
            return 0; // Not safe
    }
    return 1; // Safe
}

int main() {
    clrscr(); // Clear screen

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("Allocation for Process %d Resource %d: ", i + 1, j + 1);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input max matrix
    printf("Enter the max matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("Max for Process %d Resource %d: ", i + 1, j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        printf("Available Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    calculate_need();

    // Check if the system is in a safe state
    if (is_safe()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    getch(); // Wait for a key press
    return 0;
}
