#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    // El nombre del programa a ejecutar
    char *program = "ip";

    // Argumentos para el programa: el nombre del programa, "-l", "-a" y NULL al final
    char *arguments[] = {"ip", "a", NULL};

    // Llamar a execvp para ejecutar el comando ls con argumentos
    execvp(program, arguments);

    // Si execvp falla, imprimirá un error
    perror("execvp");
    return 1;
}