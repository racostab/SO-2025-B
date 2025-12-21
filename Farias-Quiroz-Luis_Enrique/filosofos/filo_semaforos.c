/*
	Programa que utiliza semaforos para resolver el problema de los filosofos
	Forma de compilar: gcc filo_semaforos.c -o filo_v2
	Ejecución: ./filo_v2
	Salida: El programa crea imprime las diferentes acciones que realizan los filosofos.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4

sem_t tenedores[N];
pthread_t filosofos[N];

void *filosofo(void *arg);
void pensar(int id);
void tomar(int id, int tenedor);
void comer(int id);
void soltar(int id, int tenedor1, int tenedor2);

int main(void)
{
    int i;
    for (i = 0; i < N; i++) 
    {
        sem_init(&tenedores[i], 0, 1);  
    }

    for (i = 0; i < N; i++) 
    {
        int *id = malloc(sizeof(int));
        if (!id) 
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *id = i;
        pthread_create(&filosofos[i], NULL, filosofo, id);
    }

    for (i = 0; i < N; i++) 
    {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}

void *filosofo(void *arg)
{
    int id = *(int *)arg;
    free(arg);

    int der = id;
    int izq = (id + (N - 1)) % N;

    int primero = izq < der ? izq : der;
    int segundo = izq < der ? der : izq;

    while (1) 
    {
        pensar(id);
        tomar(id, primero);
        tomar(id, segundo);
        comer(id);
        soltar(id, primero, segundo);
    }

    return NULL;
}

void pensar(int id)
{
    printf("Filosofo %d: pensando...\n", id);
    sleep(2);
}

void tomar(int id, int tenedor)
{
    sem_wait(&tenedores[tenedor]);
    printf("Filosofo %d tomó el tenedor %d\n", id, tenedor);
}

void comer(int id)
{
    printf("Filosofo %d: COMIENDO\n", id);
    sleep(2);
}

void soltar(int id, int tenedor1, int tenedor2)
{
    sem_post(&tenedores[tenedor1]);
    sem_post(&tenedores[tenedor2]);
    printf("Filosofo %d soltó los tenedores %d y %d\n",
           id, tenedor1, tenedor2);
}
