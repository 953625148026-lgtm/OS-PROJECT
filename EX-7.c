#include <stdio.h>
 
int main()
{
    int n, i;
    int bt[20], at[20], pr[20], wt[20], tat[20], done[20];
    float total_wt = 0, total_tat = 0;
    int completed = 0, current_time = 0;
 
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    printf("Enter Arrival Time, Burst Time and Priority (lower value = higher priority):\n");
    for (i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d - Priority: ", i + 1);
        scanf("%d", &pr[i]);
        done[i] = 0;
    }
 
    while (completed != n) {
        int idx = -1;
        int best_pr = 1000000;
 
        /* Among arrived, unfinished processes, pick the one with the
           highest priority (smallest priority number); break ties by
           arrival time */
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= current_time) {
                if (pr[i] < best_pr ||
                   (pr[i] == best_pr && idx != -1 && at[i] < at[idx])) {
                    best_pr = pr[i];
                    idx = i;
                }
            }
        }
 
        if (idx == -1) {
            current_time++;
            continue;
        }
 
        wt[idx] = current_time - at[idx];
        current_time += bt[idx];
        tat[idx] = current_time - at[idx];
        done[idx] = 1;
        completed++;
    }
 
    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }
 
    printf("\nAverage Waiting Time    = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
 
    return 0;
}
