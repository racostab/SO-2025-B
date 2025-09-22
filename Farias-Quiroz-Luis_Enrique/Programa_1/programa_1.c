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
