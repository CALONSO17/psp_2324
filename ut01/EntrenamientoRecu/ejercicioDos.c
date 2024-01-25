/*Crea un proceso que cree dos procesos hijos, luego generará N (20) números aleatorios.
Enviará los pares al primer hijo, los impares al segundo. Los hijos escribirán por pantalla "Soy el hijo 1|2, he recibido ".
Por cada número que mande el padre.*/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define NUMERO_CONSTANTE 20
#define READ 0
#define WRITE 1

int main()
{
    int fd1[2];
    int fd2[2];
    int number;
    // Crear un pipe
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t hijo1, hijo2;

    hijo1 = fork();

    if (hijo1 == -1)
    {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo1 == 0)
    {
        close(fd1[WRITE]);
        close(fd2[READ]);
        close(fd2[WRITE]);

        while (read(fd1[0], &number, sizeof(int)) > 0)
        {
            printf("Soy el hijo 1, he recibido %d\n", number);
        }

        close(fd1[READ]);
        exit(EXIT_SUCCESS);
    }

    hijo2 = fork();

    if (hijo2 == -1)
    {
        perror("Error al crear el segundo hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo2 == 0)
    {
        close(fd2[WRITE]);
        close(fd1[READ]);
        close(fd1[WRITE]);

        while (read(fd2[0], &number, sizeof(int)) > 0)
        {
            printf("Soy el hijo 2, he recibido %d\n", number);
        }

        close(fd2[READ]);
        exit(EXIT_SUCCESS);
    }
    close(fd1[READ]);
    close(fd2[READ]);
    for (int i = 0; i < NUMERO_CONSTANTE; i++)
    {
        number = rand() % 100 + 1;
        if (number % 2 == 0)
        {
            write(fd1[WRITE], &number, sizeof(number));
        }
        else
        {
            write(fd2[WRITE], &number, sizeof(number));
        }
    }
    close(fd1[WRITE]);
    close(fd2[WRITE]);

    waitpid(hijo1, NULL, 0);
    waitpid(hijo2, NULL, 0);
    return 0;
}