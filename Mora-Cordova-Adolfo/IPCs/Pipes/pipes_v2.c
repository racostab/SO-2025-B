#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{

int error, fd[2], pid, tam=5;
char *buf="abcde";

	error = pipe(fd);
	if (error < 0) {
		printf("Error creating pipe\n");
		return 1;
	}

	pid = fork();
	switch (pid) {
		case -1:
			printf("Error creating process\n");
			exit (1);
		case 0: // Child process
			read(fd[0], buf, tam);
			printf("H %s %d\n", buf);
			break;
		default: // Parent process
			sleep(15);
			write(fd[1], buf, tam);
			printf("P %s \n", buf);
			break;
	}
} 
		