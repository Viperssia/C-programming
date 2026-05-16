#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char** lines;
    int count;
} thread_data_t;

void* print_lines(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;

    for(int i = 0; i < data->count; i++) {
        printf("%s\n", data->lines[i]);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    thread_data_t data[4];
    
    char* strings1[] = {"Поток 1: Привет", "Поток 1: Мир"};
    char* strings2[] = {"Поток 2: Hello", "Поток 2: World"};
    char* strings3[] = {"Поток 3: Bonjour", "Поток 3: Monde"};
    char* strings4[] = {"Поток 4: Hola", "Поток 4: Mundo"};
    
    data[0].lines = strings1;
    data[0].count = 2;
    data[1].lines = strings2;
    data[1].count = 2;
    data[2].lines = strings3;
    data[2].count = 2;
    data[3].lines = strings4;
    data[3].count = 2;
    
    for(int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, print_lines, &data[i]);
    }
    
    for(int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}