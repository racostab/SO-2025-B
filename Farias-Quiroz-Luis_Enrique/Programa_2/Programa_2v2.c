/*
	Programa que utiliza llamadas de sistema para crear y escribir en un archivo
	Forma de compilar: gcc Programa_2v2.c -o programa2
	Ejecución: ./programa2
	Salida: El programa crea un archivo en la carpeta que fue ejecutado llamado "nuevo.txt"
	en este se escribe lo que contenga la cadena texto.
*/

#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	pid_t tid;
	tid = syscall(SYS_gettid);
	printf("PID obtenido: %d\n",tid);

	const char *texto = "Prueba para escribir en archivo";
	ssize_t longitud = strlen(texto);
	

	int fd;
	fd = syscall(SYS_open,"nuevo.txt", O_CREAT | O_RDWR | O_TRUNC , 0644);

	int escritos = syscall(SYS_write,fd,texto,longitud);
	close(fd);
}
