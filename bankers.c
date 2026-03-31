#include <stdio.h>

#define MAX 10

int n, m; // n = processes, m = resources
int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int available[MAX];
int safeSeq[MAX];

void calculateNeed() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe() {
    int work[MAX], finish[MAX] = {0};
    int count = 0;

    for(int i = 0; i < m; i++)
        work[i] = available[i];

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in safe state (Deadlock possible)\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state\nSafe sequence: ");
    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");
    return 1;
}

void resourceRequest() {
    int process;
    int request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    printf("Enter request for each resource:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    // Check request <= need
    for(int i = 0; i < m; i++) {
        if(request[i] > need[process][i]) {
            printf("\nError: Request exceeds maximum need\n");
            return;
        }
    }

    // Check request <= available
    for(int i = 0; i < m; i++) {
        if(request[i] > available[i]) {
            printf("\nResources not available, process must wait\n");
            return;
        }
    }

    // Pretend allocation
    for(int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    printf("\nChecking system state after allocation...\n");

    if(isSafe()) {
        printf("Request can be GRANTED\n");
    } else {
        printf("Request CANNOT be granted (Unsafe state)\n");

        // Rollback
        for(int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    calculateNeed();

    if(isSafe()) {
        char choice;
        printf("\nDo you want to make a resource request? (y/n): ");
        scanf(" %c", &choice);

        if(choice == 'y' || choice == 'Y') {
            resourceRequest();
        }
    }

    return 0;
}