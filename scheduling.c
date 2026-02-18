#include <stdio.h>

struct Process {
    int pid;
    int bt, at, pr;
    int wt, tat, ct;
    int remaining;
    int completed;
};

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

/* ✅ Function Declarations */
void FCFS(struct Process p[], int n);
void SRTF(struct Process p[], int n);
void PriorityNP(struct Process p[], int n);
void RoundRobin(struct Process p[], int n, int q);

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

    while(1) {
        printf("\n\n--- CPU Scheduling Menu ---\n");
        printf("1. FCFS\n");
        printf("2. SRTF\n");
        printf("3. Non-preemptive Priority\n");
        printf("4. Round Robin (q=3)\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice==5) break;

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

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

/* ========================================================= */
/* ✅ FCFS Scheduling */
void FCFS(struct Process p[], int n) {
    int time = 0;

    for(int i=0;i<n;i++) {
        if(time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }
}

/* ✅ SRTF Scheduling */
void SRTF(struct Process p[], int n) {
    int time=0, done=0;

    while(done < n) {
        int idx=-1, min=9999;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && p[i].remaining > 0) {
                if(p[i].remaining < min) {
                    min = p[i].remaining;
                    idx = i;
                }
            }
        }

        if(idx==-1) { time++; continue; }

        p[idx].remaining--;
        time++;

        if(p[idx].remaining==0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }
}

/* ✅ Priority Non-preemptive */
void PriorityNP(struct Process p[], int n) {
    int time=0, done=0;

    while(done < n) {
        int idx=-1, high=-1;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && p[i].completed==0) {
                if(p[i].pr > high) {
                    high = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx==-1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;

        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].completed=1;
        done++;
    }
}

/* ✅ Round Robin Scheduling */
void RoundRobin(struct Process p[], int n, int q) {
    int time=0, done=0;

    while(done < n) {
        int executed=0;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && p[i].remaining > 0) {

                executed=1;
                int slice = (p[i].remaining > q) ? q : p[i].remaining;

                p[i].remaining -= slice;
                time += slice;

                if(p[i].remaining==0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }

        if(!executed) time++;
    }
}
