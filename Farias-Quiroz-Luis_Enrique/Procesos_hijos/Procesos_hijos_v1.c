/*
Programa que crea un copia de un proceso y muestra el PID del proceso padre e hijo
Compilación: gcc Procesos_hijos_v1.c -o Procesosv1
Ejecución: ./Procesosv1
Salida:   PID padre: #PID
          PID hijo: #PID

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
