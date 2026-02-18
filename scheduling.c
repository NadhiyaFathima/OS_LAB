#include <stdio.h>

struct Process {
    int pid;
    int bt, at, pr;
    int wt, tat, ct;
    int remaining;
    int completed;
};

void FCFS(struct Process p[], int n);
void SRTF(struct Process p[], int n);
void PriorityNP(struct Process p[], int n);
void RoundRobin(struct Process p[], int n, int q);

float avgWaiting(struct Process p[], int n) {
    float sum = 0;
    for(int i=0;i<n;i++)
        sum += p[i].wt;
    return sum/n;
}

void reset(struct Process p[], struct Process copy[], int n) {
    for(int i=0;i<n;i++) {
        p[i] = copy[i];
        p[i].remaining = p[i].bt;
        p[i].completed = 0;
    }
}

int main() {
    int n, choice;
    struct Process p[20], copy[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++) {
        printf("\nProcess %d\n",i+1);
        p[i].pid = i+1;

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        copy[i] = p[i];
    }

    float fcfsAvg, srtfAvg, prAvg, rrAvg;

    while(1) {
        printf("\n\n--- CPU Scheduling Menu ---\n");
        printf("1. FCFS\n");
        printf("2. SRTF\n");
        printf("3. Non-preemptive Priority\n");
        printf("4. Round Robin (q=3)\n");
        printf("5. Compare All\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice==6) break;

        switch(choice) {

            case 1:
                reset(p,copy,n);
                FCFS(p,n);
                printf("Average WT = %.2f\n", avgWaiting(p,n));
                break;

            case 2:
                reset(p,copy,n);
                SRTF(p,n);
                printf("Average WT = %.2f\n", avgWaiting(p,n));
                break;

            case 3:
                reset(p,copy,n);
                PriorityNP(p,n);
                printf("Average WT = %.2f\n", avgWaiting(p,n));
                break;

            case 4:
                reset(p,copy,n);
                RoundRobin(p,n,3);
                printf("Average WT = %.2f\n", avgWaiting(p,n));
                break;

            case 5:
                reset(p,copy,n);
                FCFS(p,n);
                fcfsAvg = avgWaiting(p,n);

                reset(p,copy,n);
                SRTF(p,n);
                srtfAvg = avgWaiting(p,n);

                reset(p,copy,n);
                PriorityNP(p,n);
                prAvg = avgWaiting(p,n);

                reset(p,copy,n);
                RoundRobin(p,n,3);
                rrAvg = avgWaiting(p,n);

                printf("\n--- Average Waiting Times ---\n");
                printf("FCFS      = %.2f\n",fcfsAvg);
                printf("SRTF      = %.2f\n",srtfAvg);
                printf("Priority  = %.2f\n",prAvg);
                printf("RR (q=3)  = %.2f\n",rrAvg);

                float min = fcfsAvg;
                char best[20] = "FCFS";

                if(srtfAvg < min) { min=srtfAvg; sprintf(best,"SRTF"); }
                if(prAvg < min)   { min=prAvg; sprintf(best,"Priority"); }
                if(rrAvg < min)   { min=rrAvg; sprintf(best,"Round Robin"); }

                printf("\n✅ Best Algorithm = %s (Min Avg WT = %.2f)\n",best,min);
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
