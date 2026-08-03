#include <stdio.h>
 
int main()
{
    int n, i;
    int bt[20], at[20], wt[20], tat[20], done[20];
    float total_wt = 0, total_tat = 0;
    int completed = 0, current_time = 0;
 
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        done[i] = 0;
    }
 
    while (completed != n) {
        int idx = -1;
        int min_bt = 1000000;
 
        /* Among the processes that have arrived and are not done,
           pick the one with the smallest burst time */
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= current_time) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }
 
        if (idx == -1) {
            /* No process has arrived yet, CPU is idle */
            current_time++;
            continue;
        }
 
        wt[idx] = current_time - at[idx];
        current_time += bt[idx];
        tat[idx] = current_time - at[idx];
        done[idx] = 1;
        completed++;
    }
 
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
 
    printf("\nAverage Waiting Time    = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
 
    return 0;
}

