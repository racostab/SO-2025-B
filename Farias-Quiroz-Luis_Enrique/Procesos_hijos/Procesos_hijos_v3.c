/*
Programa que crea un copia de un proceso y N procesos hijos, los cuales se imprimen para poder observar el tiempo
en el que tienen el control de la consola.
Compilación: gcc Procesos_hijos_v3.c -o Procesosv3
Ejecución: ./Procesosv3
Salida:   
    PID_PADRE  PID_HIJO_1  PID_HIJO_2  PID_HIJO_N
	  PID_PADRE  PID_HIJO_1  PID_HIJO_2  PID_HIJO_N
	  PID_PADRE  PID_HIJO_1  PID_HIJO_2  PID_HIJO_N
	  PID_PADRE  PID_HIJO_1  PID_HIJO_2  PID_HIJO_N
	  PID_PADRE  PID_HIJO_1  PID_HIJO_2  PID_HIJO_N

*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


void hijo(int columna);
int main()
{
	pid_t pid;
	pid_t my_pid;
	int N;
       //pid = fork();

	for(N=0;N<=5;N++)
	{
		pid = fork();
		switch(pid)
       		{
            	case -1:
		      	printf("Error en la creación del proceso");
                break;
            	case 0: 
                	hijo(N+1);
                break;    
            	default:
                	my_pid = getpid();
                	printf("PID padre: %d\n", my_pid);
                break; 
        	}	
	}
}
void hijo(int columna)
{	
	pid_t my_pid = getpid();
	while(1)
	{
	for (int j= 0; j < columna;j++)
	{
		printf("\t");
	}
        printf("%d\n",my_pid);
	usleep(200000);
	}
}
