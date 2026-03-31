#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define DISK_SIZE 5000

// Sort helper
void sort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// SSTF
int sstf(int req[], int n, int head) {
    int visited[MAX] = {0};
    int total = 0;

    for(int i = 0; i < n; i++) {
        int min = 10000, index = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j]) {
                int dist = abs(head - req[j]);
                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        total += min;
        head = req[index];
        visited[index] = 1;
    }

    return total;
}

// LOOK
int look(int req[], int n, int head) {
    int total = 0;
    int temp[MAX];

    for(int i = 0; i < n; i++)
        temp[i] = req[i];

    sort(temp, n);

    int pos;
    for(pos = 0; pos < n; pos++) {
        if(temp[pos] >= head)
            break;
    }

    // Move right
    for(int i = pos; i < n; i++) {
        total += abs(head - temp[i]);
        head = temp[i];
    }

    // Then left
    for(int i = pos - 1; i >= 0; i--) {
        total += abs(head - temp[i]);
        head = temp[i];
    }

    return total;
}

// CSCAN
int cscan(int req[], int n, int head) {
    int total = 0;
    int temp[MAX];

    for(int i = 0; i < n; i++)
        temp[i] = req[i];

    sort(temp, n);

    int pos;
    for(pos = 0; pos < n; pos++) {
        if(temp[pos] >= head)
            break;
    }

    // Move right
    for(int i = pos; i < n; i++) {
        total += abs(head - temp[i]);
        head = temp[i];
    }

    // Go to end
    total += abs(head - (DISK_SIZE - 1));
    head = 0;

    // Jump to start (circular)
    total += (DISK_SIZE - 1);

    // Continue from start
    for(int i = 0; i < pos; i++) {
        total += abs(head - temp[i]);
        head = temp[i];
    }

    return total;
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s <initial_head_position>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);
    int req[MAX];

    srand(time(0));

    printf("Disk Requests:\n");
    for(int i = 0; i < MAX; i++) {
        req[i] = rand() % DISK_SIZE;
        printf("%d ", req[i]);
    }
    printf("\n");

    int sstf_move = sstf(req, MAX, head);
    int look_move = look(req, MAX, head);
    int cscan_move = cscan(req, MAX, head);

    printf("\nTotal Head Movements:\n");
    printf("SSTF: %d\n", sstf_move);
    printf("LOOK: %d\n", look_move);
    printf("CSCAN: %d\n", cscan_move);

    return 0;
}