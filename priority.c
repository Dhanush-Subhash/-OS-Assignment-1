#include <stdio.h>

struct Process {
    char pid[5];
    int at, bt, pr;
    int wt, tat, completed;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input section with prompts
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        printf("Process ID: ");
        scanf("%s", p[i].pid);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority (lower value = higher priority): ");
        scanf("%d", &p[i].pr);

        p[i].completed = 0;
    }

    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Find process with highest priority
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                } else if (p[i].pr == highest_priority) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            printf("\nAt time %d, Process %s is selected (Priority: %d)\n",
                   time, p[idx].pid, p[idx].pr);

            p[idx].wt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].tat = p[idx].wt + p[idx].bt;
            p[idx].completed = 1;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        } else {
            printf("\nAt time %d, CPU is idle\n", time);
            time++;
        }
    }

    // Output
    printf("\n===== RESULT =====\n");

    printf("\nWaiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %d\n", p[i].pid, p[i].wt);
    }

    printf("\nTurnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %d\n", p[i].pid, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
