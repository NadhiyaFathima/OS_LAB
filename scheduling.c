#include <stdio.h>

struct Process {
    int pid;
    int at, bt, pr;
    int ct, tat, wt;
    int remaining;
    int completed;
};

/* ---------------- Utility Functions ---------------- */

void reset(struct Process p[], struct Process copy[], int n) {
    for(int i=0;i<n;i++) {
        p[i] = copy[i];
        p[i].remaining = p[i].bt;
        p[i].completed = 0;
    }
}

float averageWT(struct Process p[], int n) {
    float sum = 0;
    for(int i=0;i<n;i++)
        sum += p[i].wt;
    return sum/n;
}

void printTable(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    printf("------------------------------------------------------------\n");

    for(int i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("------------------------------------------------------------\n");
    printf("Average Waiting Time = %.2f\n", averageWT(p,n));
}

/* ---------------- Gantt Chart Printing ---------------- */

void printGantt(int seq[], int times[], int count) {
    printf("\nGantt Chart:\n|");
    for(int i=0;i<count;i++)
        printf(" P%d |", seq[i]);

    printf("\n0");
    for(int i=0;i<count;i++)
        printf("  %d", times[i]);

    printf("\n");
}

/* ---------------- 1. FCFS ---------------- */

void FCFS(struct Process p[], int n) {
    int time = 0;
    int seq[50], times[50], count=0;

    for(int i=0;i<n;i++) {
        if(time < p[i].at)
            time = p[i].at;

        seq[count] = p[i].pid;
        time += p[i].bt;
        times[count] = time;
        count++;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }

    printf("\n========== FCFS Scheduling ==========\n");
    printTable(p,n);
    printGantt(seq,times,count);
}

/* ---------------- 2. SRTF ---------------- */

void SRTF(struct Process p[], int n) {
    int time=0, done=0;
    int seq[100], times[100], count=0;
    int last=-1;

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

        if(idx==-1) {
            time++;
            continue;
        }

        if(last != p[idx].pid) {
            seq[count] = p[idx].pid;
            times[count] = time;
            count++;
            last = p[idx].pid;
        }

        p[idx].remaining--;
        time++;

        if(p[idx].remaining == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }

    times[count] = time;

    printf("\n========== SRTF Scheduling ==========\n");
    printTable(p,n);
    printGantt(seq,times,count);
}

/* ---------------- 3. Priority Non-Preemptive ---------------- */

void PriorityNP(struct Process p[], int n) {
    int time=0, done=0;
    int seq[50], times[50], count=0;

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

        if(idx==-1) {
            time++;
            continue;
        }

        seq[count] = p[idx].pid;
        time += p[idx].bt;
        times[count] = time;
        count++;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;

        p[idx].completed = 1;
        done++;
    }

    printf("\n====== Priority Non-Preemptive Scheduling ======\n");
    printTable(p,n);
    printGantt(seq,times,count);
}

/* ---------------- 4. Round Robin ---------------- */

void RoundRobin(struct Process p[], int n, int q) {
    int time=0, done=0;
    int seq[100], times[100], count=0;

    while(done < n) {
        int executed=0;

        for(int i=0;i<n;i++) {
            if(p[i].at <= time && p[i].remaining > 0) {

                executed = 1;
                seq[count] = p[i].pid;

                int slice = (p[i].remaining > q) ? q : p[i].remaining;

                time += slice;
                p[i].remaining -= slice;

                times[count] = time;
                count++;

                if(p[i].remaining == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt  = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }

        if(!executed)
            time++;
    }

    printf("\n========== Round Robin Scheduling (q=3) ==========\n");
    printTable(p,n);
    printGantt(seq,times,count);
}

/* ---------------- MAIN ---------------- */

int main() {
    int n;
    struct Process p[20], copy[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++) {
        p[i].pid = i+1;

        printf("\nProcess P%d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        copy[i] = p[i];
    }

    float fcfsAvg, srtfAvg, prAvg, rrAvg;

    reset(p,copy,n);
    FCFS(p,n);
    fcfsAvg = averageWT(p,n);

    reset(p,copy,n);
    SRTF(p,n);
    srtfAvg = averageWT(p,n);

    reset(p,copy,n);
    PriorityNP(p,n);
    prAvg = averageWT(p,n);

    reset(p,copy,n);
    RoundRobin(p,n,3);
    rrAvg = averageWT(p,n);

    printf("\n\n========= FINAL COMPARISON =========\n");
    printf("FCFS Avg WT      = %.2f\n", fcfsAvg);
    printf("SRTF Avg WT      = %.2f\n", srtfAvg);
    printf("Priority Avg WT  = %.2f\n", prAvg);
    printf("RR Avg WT (q=3)  = %.2f\n", rrAvg);

    float min = fcfsAvg;
    char best[30] = "FCFS";

    if(srtfAvg < min) { min = srtfAvg; sprintf(best,"SRTF"); }
    if(prAvg < min)   { min = prAvg;   sprintf(best,"Priority"); }
    if(rrAvg < min)   { min = rrAvg;   sprintf(best,"Round Robin"); }

    printf("\n✅ Best Algorithm = %s (Minimum Avg WT = %.2f)\n", best, min);

    return 0;
}
