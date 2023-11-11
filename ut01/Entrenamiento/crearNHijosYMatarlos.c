#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int hijos;
    pid_t id;

    // El nombre del programa a ejecutar
    char *program = "kill";

    // Argumentos para el programa: el nombre del programa, "-9" y NULL al final
    char *arguments[] = {"kill", "-9", NULL};

    // Solicitar al usuario el número de hijos
    printf("¿Cuantos hijos quieres?\n");
    scanf("%d", &hijos);

    // Crear n hijos
    for (int i = 0; i < hijos; i++) {
        id = fork();
        if (id == 0) {
            // Código del proceso hijo
            printf("Soy el hijo %d y me acaban de crear\n", getpid());
            pause();  // Esperar señal
            exit(0);  // Salir del proceso hijo
        }
    }

    // Esperar a que todos los hijos estén listos
    sleep(2);

    // Enviar la señal SIGKILL a todos los hijos
    for (int i = 0; i < hijos; i++) {
        kill(0, SIGKILL);
    }

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < hijos; i++) {
        wait(NULL);
    }

    // Ejecutar el comando "kill" para confirmar que los procesos han sido terminados
    execvp(program, arguments);

    return 0;
}
