#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Function to check if page is in frames
int search(int key, int frame[], int f) {
    for(int i = 0; i < f; i++) {
        if(frame[i] == key)
            return 1;
    }
    return 0;
}

// FIFO
int fifo(int pages[], int n, int f) {
    int frame[10], index = 0, faults = 0;

    for(int i = 0; i < f; i++)
        frame[i] = -1;

    for(int i = 0; i < n; i++) {
        if(!search(pages[i], frame, f)) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }
    return faults;
}

// LRU
int lru(int pages[], int n, int f) {
    int frame[10], time[10], faults = 0, counter = 0;

    for(int i = 0; i < f; i++)
        frame[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found) {
            int min = 0;
            for(int j = 1; j < f; j++) {
                if(time[j] < time[min])
                    min = j;
            }

            frame[min] = pages[i];
            counter++;
            time[min] = counter;
            faults++;
        }
    }
    return faults;
}

// Optimal
int optimal(int pages[], int n, int f) {
    int frame[10], faults = 0;

    for(int i = 0; i < f; i++)
        frame[i] = -1;

    for(int i = 0; i < n; i++) {
        if(search(pages[i], frame, f))
            continue;

        int pos = -1, farthest = i + 1;

        for(int j = 0; j < f; j++) {
            int k;
            for(k = i + 1; k < n; k++) {
                if(frame[j] == pages[k]) {
                    if(k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                    break;
                }
            }

            if(k == n) { // not used again
                pos = j;
                break;
            }
        }

        if(pos == -1)
            pos = 0;

        frame[pos] = pages[i];
        faults++;
    }

    return faults;
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage: %s <length> <frames (1-7)>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int f = atoi(argv[2]);

    if(f < 1 || f > 7) {
        printf("Frames must be between 1 and 7\n");
        return 1;
    }

    int pages[MAX];

    srand(time(0));

    printf("Page Reference String:\n");
    for(int i = 0; i < n; i++) {
        pages[i] = rand() % 10; // 0–9
        printf("%d ", pages[i]);
    }
    printf("\n");

    int fifo_faults = fifo(pages, n, f);
    int lru_faults = lru(pages, n, f);
    int opt_faults = optimal(pages, n, f);

    printf("\nPage Faults:\n");
    printf("FIFO: %d\n", fifo_faults);
    printf("LRU: %d\n", lru_faults);
    printf("Optimal: %d\n", opt_faults);

    return 0;
}