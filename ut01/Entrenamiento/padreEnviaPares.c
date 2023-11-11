#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define N 20

int main() {
    srand(time(NULL));

    // Creamos dos tuberías (pipes) para comunicarnos con los hijos
    int fd1[2]; // Tubería para el primer hijo
    int fd2[2]; // Tubería para el segundo hijo

    // Comprobamos si la creación de las tuberías tuvo éxito
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child1, child2;

    

    // Creamos el primer hijo
    child1 = fork();

    if (child1 == -1) {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) { // Código para el primer hijo
        //Hay que cerrar el hijo que no se usa
        close(fd1[1]); // Cerramos el extremo de escritura, el primer hijo solo va a leer
        close(fd2[1]);
        close(fd2[0]);
        int number;
        printf("Soy el hijo 1, he recibido: ");
        
        while (read(fd1[0], &number, sizeof(int)) > 0) {
            printf("%d ", number);
            fflush(stdout);
        }
        printf("\n");
        close(fd1[0]); // Cerramos el extremo de lectura una vez terminada la lectura
        
        exit(EXIT_SUCCESS);
    }

    // Creamos el segundo hijo
    child2 = fork();

    if (child2 == -1) {
        perror("Error al crear el segundo hijo");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) { // Código para el segundo hijo
        //Hay que cerrar el hijo que no se usa
        close(fd2[1]); // Cerramos el extremo de escritura, el segundo hijo solo va a leer
        close(fd1[1]);
        close(fd1[0]);
        int number;
        printf("Soy el hijo 2, he recibido: ");
        while (read(fd2[0], &number, sizeof(int)) > 0) {
            printf("%d ", number);
        }
        printf("\n");
        close(fd2[0]); // Cerramos el extremo de lectura una vez terminada la lectura
        exit(EXIT_SUCCESS);
    }

    // Código para el padre

    // Generamos N números aleatorios y los enviamos a los hijos
    for (int i = 0; i < N; i++) {
        printf("Hola soy el padre, he generado: ");
        int number = rand() % 100;
        printf("%d\n", number);
        if (number % 2 == 0) {
            write(fd1[1], &number, sizeof(int)); // Enviar número par al primer hijo
        } else {
            write(fd2[1], &number, sizeof(int)); // Enviar número impar al segundo hijo
        }
    }
    
    close(fd1[0]); // Cerramos el extremo de lectura del primer hijo
    close(fd2[0]); // Cerramos el extremo de lectura del segundo hijo

    

    close(fd1[1]); // Cerramos el extremo de escritura del primer hijo
    close(fd2[1]); // Cerramos el extremo de escritura del segundo hijo

    // Esperamos a que ambos hijos terminen antes de salir
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}