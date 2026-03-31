#include <stdio.h>

#define MAX 10

int main() {
    int n, m; // n = processes, m = resources
    int allocation[MAX][MAX], request[MAX][MAX];
    int available[MAX];
    int work[MAX], finish[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize
    for(int i = 0; i < m; i++)
        work[i] = available[i];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if(found == 0)
            break;
    }

    // Check deadlock
    int deadlock = 0;

    for(int i = 0; i < n; i++) {
        if(finish[i] == 0) {
            deadlock = 1;
            printf("\nProcess P%d is deadlocked", i);
        }
    }

    if(deadlock == 0) {
        printf("\n\nSystem is NOT in deadlock\n");
    } else {
        printf("\n\nSystem is in DEADLOCK\n");
    }

    return 0;
}