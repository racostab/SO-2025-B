/*
	Programa para observar la creación de un proceso padre y un proceso hijo
	Forma de compilar: gcc programa_1.c -o programa1
	Ejecución: ./programa1
	Salida: El programa imprime el ID del proceso padre y el ID del proceso hijo
*/


#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


int main() 
{
    pid_t pid;
    pid_t my_pid;
    pid = fork();
        switch(pid)
        {
            case -1: printf("Error en la creación del proceso");
                break;
            case 0: 
                my_pid = getpid();
                printf("PID hijo: %d\n", my_pid);
                break;    
            default:
                my_pid = getpid();
            
                printf("PID padre: %d\n", my_pid);
                break; 
        }
}
