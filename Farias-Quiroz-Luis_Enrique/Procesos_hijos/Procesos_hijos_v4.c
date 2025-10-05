/*
Programa que cuenta la cantidad de procesos creados
Compilación: gcc Procesos_hijos_v4.c -o Procesosv4
Ejecución: ./Procesosv4
Salida:   Total: #Procesos

*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
int main() 
{
    int *contador = mmap(NULL, sizeof(int),
		        PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS,
			-1, 0);
    *contador = 0;
    for (int i=1;i<=3;i++)
    {   
	pid_t pid = fork();    
    	if (pid == -1)
    	{
    		printf("Error");
	}
	else if(pid > 0)
	{
		(*contador)++;
	}
    }
     if (getpid() == getppid() + 1 || getpid() == getppid()) {
        // Esperar a todos los hijos
        int status;
        while (wait(&status) > 0);
        printf("Total: %d\n", *contador);
    }
    return 0;
}
