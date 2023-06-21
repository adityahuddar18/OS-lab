#include <stdio.h>

struct Process {
    int pid;     
    int burst;   
};

void fcfs(struct Process *processes, int n) {
    int waitingTime[n], turnaroundTime[n];
    waitingTime[0] = 0;

    
    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i - 1].burst + waitingTime[i - 1];
    }

    
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burst + waitingTime[i];
    }

    
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

   
    printf("FCFS Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, waitingTime[i], turnaroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n\n", avgTurnaroundTime);
}

void sjf(struct Process *processes, int n) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

   
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst > processes[j + 1].burst) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

   
    for (int i = 0; i < n; i++) {
        waitingTime[i] = totalWaitingTime;
        totalWaitingTime += processes[i].burst;
        turnaroundTime[i] = totalTurnaroundTime + processes[i].burst;
        totalTurnaroundTime += processes[i].burst;
    }

   
    float avgWaitingTime = totalWaitingTime / (float)n;
    float avgTurnaroundTime = totalTurnaroundTime / (float)n;

    // Displaying result
    printf("SJF (Non-preemptive) Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, waitingTime[i], turnaroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n\n", avgTurnaroundTime);
}

void srt(struct Process *processes, int n) {
    int remainingTime[n], waitingTime[n], turnaroundTime[n];
    int totalTime = 0, completed = 0;

   
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burst;
        totalTime += processes[i].burst;
    }

    while (completed < n) {
        int shortestTime = totalTime + 1;
        int shortestIndex = -1;


        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && remainingTime[i] < shortestTime) {
                shortestTime = remainingTime[i];
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1)
            break;

        remainingTime[shortestIndex]--;

        if (remainingTime[shortestIndex] == 0) {
            completed++;
            waitingTime[shortestIndex] = totalTime - processes[shortestIndex].burst;
            turnaroundTime[shortestIndex] = totalTime + 1;
        }

        totalTime++;
    }

   
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    
    printf("SRT (Shortest Remaining Time) Scheduling Algorithm\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, waitingTime[i], turnaroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n\n", avgTurnaroundTime);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].pid = i + 1;
    }

   
    fcfs(processes, n);

    
    sjf(processes, n);

   
    srt(processes, n);

    return 0;
}
