#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* _) {
    for(int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    
    for(int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
    }
    
    pthread_join(thread, NULL);
    return 0;
}