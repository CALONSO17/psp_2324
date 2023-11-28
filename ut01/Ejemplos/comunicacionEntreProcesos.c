
/*Comunicación entre procesos

La función pipe se utiliza para crear un "canal de comunicación" entre dos procesos en un sistema operativo. Imagina que es como un tubo: un proceso introduce información en un extremo del tubo y otro proceso recoge esa información del otro extremo. Esta "información" viaja solo en una dirección, es decir, de un proceso a otro, pero no viceversa.
En términos técnicos, pipe crea dos puntos de acceso o "descriptores de archivo": uno para leer y otro para escribir. Estos descriptores son simplemente números que representan puntos de acceso al sistema para leer o escribir datos.
Al llamar a pipe, le proporcionas un arreglo de dos elementos. pipe llenará este arreglo con dos números: el primero será el descriptor para leer y el segundo para escribir.

Puntos:
fd[0]: Es el descriptor que usas si quieres leer datos del pipe.
fd[1]: Es el descriptor que usas si quieres escribir datos en el pipe.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
    int fd[2];
    pid_t pid;

    // Crear un pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Bifurcar el proceso actual para crear un proceso hijo
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Código del proceso hijo
        int numero_recibido;
        close(fd[WRITE]);  // El hijo no escribirá en el pipe, así que cerramos el descriptor de escritura

        // Leer el número del pipe
        read(fd[READ], &numero_recibido, sizeof(numero_recibido));
        close(fd[READ]);  // Cerrar el descriptor de lectura después de leer

        // Imprimir el número recibido
        printf("Proceso hijo recibió el número: %d\n", numero_recibido);
        exit(EXIT_SUCCESS);

    } else {  // Código del proceso padre
        int numero_a_enviar = 42;  // Este es el número que el padre enviará al hijo
        close(fd[READ]);  // El padre no leerá del pipe, así que cerramos el descriptor de lectura

        // Escribir el número en el pipe
        write(fd[WRITE], &numero_a_enviar, sizeof(numero_a_enviar));
        close(fd[WRITE]);  // Cerrar el descriptor de escritura después de escribir

        // Esperar a que el proceso hijo termine
        wait(NULL);
        printf("Proceso padre terminó\n");
    }

    return 0;
}