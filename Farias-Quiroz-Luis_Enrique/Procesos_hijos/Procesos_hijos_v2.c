/*
Programa que crea un copia de un proceso y muestra el PID del proceso padre e hijo
Compilación: gcc Procesos_hijos_v2.c -o Procesosv2
Ejecución: ./Procesosv2
Salida:   PID padre: #PID
          PID hijo: #PID

*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void hijo();
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
                hijo();      
                break;    
            default:
                my_pid = getpid();
                printf("PID padre: %d\n", my_pid);
                break; 

        }
return 0;
}

void hijo()
{
        pid_t my_pid = getpid();
        printf("PID hijo: %d\n",my_pid);
}
