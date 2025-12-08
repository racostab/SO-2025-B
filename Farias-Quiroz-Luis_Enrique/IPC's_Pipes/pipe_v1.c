/*
Programa para creación de un pipe en c, el cual imprime la longitud del pipe creado
Compilación: gcc pipe_v1.c -o pipe_v1
Ejecución: ./pipe_v1
Salida:  longitud del pipe
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
                  
int main()
{
	int i, error, fd[2];
	char *buf = "a";

	error = pipe(fd);
	if(error){
		printf("Error en la creacion del pipe");
		return i;
	}	

	for (i=0; ; i++){
	write(fd[1],buf,1);
	printf("%d\n",i);
	fflush(stdout);
	}
}
