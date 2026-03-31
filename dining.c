#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room; // limits philosophers to N-1

void* philosopher(void* num) {
    int id = *(int*)num;

    while(1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // enter room
        sem_wait(&room);

        // pick forks
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // put forks back
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        // leave room
        sem_post(&room);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    pthread_t ph[N];
    int ids[N];

    // initialize semaphores
    sem_init(&room, 0, N - 1); // key to avoid deadlock

    for(int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // create threads
    for(int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    // join threads (never ends)
    for(int i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    return 0;
}