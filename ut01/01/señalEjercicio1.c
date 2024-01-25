#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Función de controlador de señal para SIGINT
void sigusr1_handler(int signo) {
    printf("Hola\n");
    // Aquí puedes realizar acciones adicionales antes de salir si lo deseas
    exit(0);
}

void sigusr2_handler(int signo) {
    printf("Soy\n");
    // Aquí puedes realizar acciones adicionales antes de salir si lo deseas
    exit(0);
}


int main() {
    // Registrar un manejador de señales para SIGINT usando la función signal
    signal(SIGUSR1, sigusr1_handler);

    printf("Ejecuta este programa y presiona Ctrl + C para generar una señal SIGINT.\n");

    signal(SIGUSR2, sigusr2_handler);

    // Mantén el programa en ejecución para recibir la señal
    while (1) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    return 0;
}