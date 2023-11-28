#include <stdio.h>
#include <unistd.h>

int main() {
    // El nombre del programa a ejecutar
    char *program = "ip";

    // Argumentos para el programa: el nombre del programa, "a" y NULL al final
    char *arguments[] = {"ip", "a", NULL};

    // Llamar a execvp para ejecutar el comando "ip a"
    execvp(program, arguments);

    // Si execvp falla, imprimirá un error
    perror("execvp");
    return 1;
}