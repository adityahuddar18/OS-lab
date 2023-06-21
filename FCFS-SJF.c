#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
};

void fcfs(struct Process p[], int n) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;
    
    waiting_time[0] = 0; // Waiting time for the first process is always 0
    
    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + p[i - 1].burst_time;
        total_waiting_time += waiting_time[i];
    }
    
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + p[i].burst_time;
        total_turnaround_time += turnaround_time[i];
    }
    
    printf("FCFS Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    // Print process details
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void sjf(struct Process p[], int n) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;
    
    // Sort processes based on burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst_time > p[j + 1].burst_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    waiting_time[0] = 0; // Waiting time for the first process is always 0
    
    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + p[i - 1].burst_time;
        total_waiting_time += waiting_time[i];
    }
    
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + p[i].burst_time;
        total_turnaround_time += turnaround_time[i];
    }
    
    printf("SJF Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    // Print process details
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
    }
    
    fcfs(p, n);
    printf("\n");
    sjf(p, n);
    
    return 0;
}
