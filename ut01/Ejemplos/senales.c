
/*Señales
signal(): Establece un manejador de señal personalizado para una señal específica. Esto permite que un proceso o hilo maneje 
señales de manera personalizada cuando se producen.

kill(): Envía una señal a un proceso o grupo de procesos desde otro proceso. Esto se utiliza para la comunicación y el control entre procesos o hilos.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Función de controlador de señal para SIGINT
void sigint_handler(int signo) {
    printf("Se recibió la señal SIGINT (Ctrl + C)\n");
    // Aquí puedes realizar acciones adicionales antes de salir si lo deseas
    exit(0);
}

int main() {
    // Registrar un manejador de señales para SIGINT usando la función signal
    signal(SIGINT, sigint_handler);

    printf("Ejecuta este programa y presiona Ctrl + C para generar una señal SIGINT.\n");

    // Mantén el programa en ejecución para recibir la señal
    while (1) {
        sleep(1);
    }

    return 0;
}


//Ejemplos
//Ejecución de comandos
#include <stdio.h>
#include <unistd.h>

int main() {
    // El nombre del programa a ejecutar
    char *program = "ls";

    // Argumentos para el programa: el nombre del programa, "-l", "-a" y NULL al final
    char *arguments[] = {"ls", "-l", "-a", NULL};

    // Llamar a execvp para ejecutar el comando ls con argumentos
    execvp(program, arguments);

    // Si execvp falla, imprimirá un error
    perror("execvp");
    return 1;
}
