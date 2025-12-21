/*
	Programa que utiliza pipes para resolver el problema de los filosofos
	Forma de compilar: gcc filo_pipes.c -o filo_v1
	Ejecución: ./filo_v1
	Salida: El programa crea imprime las diferentes acciones que realizan los filosofos.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define N 4             
int fork_pipes[N][2]; 

void hijo(int id);
void pensar(int id);
void tomar(int id, unsigned char disponible, int tenedor);
void comer(int id);
void soltar(int id, unsigned char disponible, int tenedor, int tenedor2);

int main()
{
        int i, error, fd[2];
        char *buf = "a";
        int new_size = 1;
        pid_t pid;
            pid_t my_pid;
            //int N = 4;
        //int fork_pipes[N][2];
        unsigned char disponible = 1;

        for(i=0;i<N;i++)
            {   
            error = pipe(fork_pipes[i]);
            if(error){
                    printf("Error en la creacion del pipe");
                    return 1;
            }
        
            if (fcntl(fork_pipes[i][1], F_SETPIPE_SZ, new_size) == -1) 
            {
                perror("fcntl F_SETPIPE_SZ");
            } 
            else 
            {
                printf("Pipe buffer size set to %d bytes.\n", new_size);
            }

            write(fork_pipes[i][1], &disponible, 1);
        }


        for(i=0;i<N;i++)
            {
                    pid = fork();
                    switch(pid)
                {
                case -1:
                    printf("Error en la creación del proceso");
                    break;
                case 0: 
                    hijo(i);
                    break;    
                default:
                    my_pid = getpid();
                    printf("PID padre: %d\n", my_pid);
                    break; 
                }
        }
}

void hijo(int id)
{
    int der = id;
    int izq = (id + (N-1)) % N;
    int primero  = izq < der ? izq : der;
    int segundo = izq < der ? der : izq;
    unsigned char disponible = 1;
   
    //if(id==N-1)
    //{
    //    izq = id;
    //    der = (id + (N-1)) % N;
    //}

    while(1)
    {   
        pensar(id);
        tomar(id,disponible,primero);
        tomar(id,disponible,segundo);
        comer(id);
        soltar(id,disponible, primero, segundo);

    }
}

void pensar(int id)
{
    printf("Filosofo %d: pensando...\n", id);
    sleep(2);
}

void tomar(int id, unsigned char disponible, int tenedor)
{
    read(fork_pipes[tenedor][0], &disponible, 1);
    printf("Filosofo %d tomó el tenedor %d\n", id, tenedor);
}

void comer(int id)
{
    printf("Filosofo %d: COMIENDO \n", id);
    sleep(2);
}

void soltar(int id, unsigned char disponible, int tenedor, int tenedor2)
{
    write(fork_pipes[tenedor][1], &disponible, 1);
    write(fork_pipes[tenedor2][1], &disponible, 1);
    printf("Filosofo %d soltó los tenedores %d y %d\n", id, tenedor, tenedor2);
} 
