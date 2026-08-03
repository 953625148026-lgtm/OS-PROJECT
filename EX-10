#include <stdio.h>
 
#define P 5   /* number of processes */
#define R 3   /* number of resource types */
 
int allocation[P][R];
int max[P][R];
int need[P][R];
int available[R];
 
void calculate_need()
{
    int i, j;
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}
 
/* Returns 1 and fills safe_seq[] if the system is in a safe state */
int is_safe(int safe_seq[])
{
    int work[R];
    int finish[P] = {0};
    int i, j, count = 0;
 
    for (i = 0; i < R; i++)
        work[i] = available[i];
 
    while (count < P) {
        int found = 0;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return 0; /* no process could proceed -> unsafe */
    }
    return 1;
}
 
/* Attempts to grant a resource request from process p_id.
   Returns 1 if granted, 0 if the request must be denied. */
int request_resources(int p_id, int request[R])
{
    int i;
    int safe_seq[P];
 
    /* Step 1: request must not exceed the process's declared need */
    for (i = 0; i < R; i++) {
        if (request[i] > need[p_id][i]) {
            printf("Error: Process P%d has exceeded its maximum claim.\n", p_id);
            return 0;
        }
    }
 
    /* Step 2: request must not exceed currently available resources */
    for (i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Process P%d must wait; resources are not available.\n", p_id);
            return 0;
        }
    }
 
    /* Step 3: tentatively allocate and check if the resulting state is safe */
    for (i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[p_id][i] += request[i];
        need[p_id][i] -= request[i];
    }
 
    if (is_safe(safe_seq)) {
        printf("Request can be granted safely.\nNew safe sequence: ");
        for (i = 0; i < P; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
        return 1;
    } else {
        /* Roll back — the request would leave the system unsafe */
        for (i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[p_id][i] -= request[i];
            need[p_id][i] += request[i];
        }
        printf("Request denied: granting it would leave the system in an unsafe state.\n");
        return 0;
    }
}
 
int main()
{
    int i, j;
 
    printf("Enter Allocation matrix (%d processes x %d resources):\n", P, R);
    for (i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);
    }
 
    printf("Enter Maximum matrix (%d processes x %d resources):\n", P, R);
    for (i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (j = 0; j < R; j++)
            scanf("%d", &max[i][j]);
    }
 
    printf("Enter Available resources vector (%d resources):\n", R);
    for (j = 0; j < R; j++)
        scanf("%d", &available[j]);
 
    calculate_need();
 
    printf("\nNeed matrix:\n");
    for (i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (j = 0; j < R; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
 
    int safe_seq[P];
    if (is_safe(safe_seq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < P; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state (deadlock may occur).\n");
        return 0;
    }
 
    /* Demonstrate a resource request */
    int p_id;
    int request[R];
    printf("\nEnter process number requesting resources: ");
    scanf("%d", &p_id);
    printf("Enter request vector (%d resources): ", R);
    for (j = 0; j < R; j++)
        scanf("%d", &request[j]);
 
    request_resources(p_id, request);
 
    return 0;
}

