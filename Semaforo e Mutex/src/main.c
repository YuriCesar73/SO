/*Threads em C. Condição de Corrida Mutex e Semáforo
Prof. Ivan L. Suptitz 19/08/2021
Explicado no vídeo: https://www.youtube.com/watch?v=y73bgQNluBk
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h> //biblioteca

#define THREADS 40 //quantas threads quero ter

long compartilhada = 0;//memoria compartilhada
sem_t mutex; //declaração

//funcao que vai executar em paralelo
void *threadFunc(void *arg)
{
	int a, b;
    for (long j = 0; j < 100000; j++) {	
        sem_wait(&mutex); //entrar na sessão crítica	
		
		a = compartilhada;
		b = 1; 
        compartilhada = a + b; //incrementando 1 (condicao de corrida)	

		sem_post(&mutex); //entrar na sessão crítica		
    }
}

int main(int argc, char *argv[]) {
    pthread_t t[THREADS];
    int s;

	sem_init(&mutex, 0, 1);//inicializar (main)
    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadFunc, NULL);//criando
    }

    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);//esperando elas terminares
    }

    printf("compartilhada = %ld\n", compartilhada);
}
