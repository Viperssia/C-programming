#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 50

void *func(void *arg) {
    sleep(*(int*)arg);
    printf("%d\n", *(int*)arg);

    return NULL;
}

void FillRand(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 30;
    }
}

int main() {
    srand(time(NULL));
    int numbers[N];
    pthread_t threads[N];

    FillRand(numbers, N);
    
    for (int i = 0; i < N; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, func, &numbers[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}