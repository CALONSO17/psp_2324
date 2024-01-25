/*Crea un proceso que cree un proceso hijo,
el envíe 3 números enteros aleatorios a través de un pipe. El proceso hijo los ordenará y los escribirá en el fichero salida.txt.*/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define READ 0
#define WRITE 1
#define NUMERO_CONSTANTE 3

int main()
{
    FILE *archivo;
    archivo = fopen("archivo.txt", "w");

    if (archivo == NULL)
    {
        perror("No se abre");
        return 1;
    }
    int fd[2];
    // Crear un pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int number;
    srand(time(NULL));
    pid_t id;
    id = fork();
    if (id == 0)
    {
        close(fd[WRITE]);

        int num1;
        int num2;
        int num3;

        read(fd[READ], &num1, sizeof(num1));
        read(fd[READ], &num2, sizeof(num2));
        read(fd[READ], &num3, sizeof(num3));

        if (num1 > num2)
        {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        if (num2 > num3)
        {
            int temp = num2;
            num2 = num3;
            num3 = temp;
        }

        if (num1 > num2)
        {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        fprintf(archivo, "%d\n%d\n%d", num1, num2, num3);

        close(fd[READ]);

        fclose(archivo);
    }
    else
    {
        close(fd[READ]);
        for (int i = 0; i < NUMERO_CONSTANTE; i++)
        {
            number = rand() % 100 + 1;
            write(fd[WRITE], &number, sizeof(number));
        }

        close(fd[WRITE]);
        wait(NULL);
    }

    return 0;
}