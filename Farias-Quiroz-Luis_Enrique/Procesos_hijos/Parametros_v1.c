/*
Programa para verificar los parametros que se proporcinaron a un programa
Compilación: gcc Parametros_v1.c -o Parametros
Ejecución: ./Parametros
Salida:  argumento: #argumentos
*/

#include<stdio.h>

int main (int argc, char *argv[])
{
	printf("argumento: %d \n",argc-1);
	if(argc==1)
		return 0;
	else
		return argc-1;
}

