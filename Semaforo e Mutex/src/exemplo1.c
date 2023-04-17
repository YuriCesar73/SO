#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS_COUNT 10

int shared_data = 0; // variável compartilhada entre as threads
sem_t sem_mutex; // semáforo usado para garantir a exclusão mútua

void *thread_func(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait(&sem_mutex); // tenta entrar na região crítica
        int temp = shared_data;
        temp = temp + 1;
        shared_data = temp; // incrementa a variável compartilhada
        printf("Thread %ld: shared_data = %d\n", (long)arg, shared_data);
        sem_post(&sem_mutex); // sai da região crítica
        usleep(100); // espera um pouco antes de continuar
    }
    pthread_exit(NULL);
}

int main() {
    int i, ret;
    pthread_t threads[THREADS_COUNT];
    
    sem_init(&sem_mutex, 0, 1); // inicializa o semáforo com valor 1

    printf("Valor inicial da variável compartilhada: %d\n", shared_data);

    for (i = 0; i < THREADS_COUNT; i++) {
        ret = pthread_create(&threads[i], NULL, thread_func, (void*)i); // cria as threads
        if (ret != 0) {
            printf("Erro ao criar a thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < THREADS_COUNT; i++) {
        ret = pthread_join(threads[i], NULL); // espera as threads terminarem
        if (ret != 0) {
            printf("Erro ao esperar a thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("Valor final da variável compartilhada: %d\n", shared_data);
    sem_destroy(&sem_mutex); // destrói o semáforo

    return 0;
}
