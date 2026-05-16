// ex7_mutex_sync.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0; // 0 - parent, 1 - child

void* child_thread(void* arg) {
    for(int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);
        while(turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Дочерний поток: строка %d\n", i);
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t child;
    pthread_create(&child, NULL, child_thread, NULL);
    
    for(int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);
        while(turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Родительский поток: строка %d\n", i);
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_join(child, NULL);
    
    return 0;
}