#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

bool senalRecibida = false;

#define READ 0
#define WRITE 1
#define RANGO_MAX 1000
#define RANGO_MIN 100

bool multiploDiez(int numero)
{
    if (numero % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool esPrimo(int numero)
{
    // Si el número es menor o igual a 1, no es primo
    if (numero <= 1)
    {
        return false;
    }

    // Verificar si el número es divisible por algún otro número diferente de 1 y él mismo
    for (int i = 2; i <= numero / 2; i++)
    {
        if (numero % i == 0)
        {
            return false; // El número no es primo
        }
    }
    return true; // El número es primo
}
// Manejador de la señal SIGUSR1
void handlerSigusr(int senal)
{
    senalRecibida = true;
    printf("He recibido la señal/n");
}

int main()
{
    int fd1[2];
    int fd2[2];
    int contadorPrimo = 0;

    if (pipe(fd1) == -1 || pipe(fd2))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t id;
    pid_t padre;

    id = fork();

    if (id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (id != 0)
    {
        padre = getppid();
        signal(SIGUSR1, handlerSigusr);
        srand(time(NULL));

        close(fd1[READ]);
        close(fd2[WRITE]);

        while (!senalRecibida)
        {
            int number = rand() % (RANGO_MAX - RANGO_MIN) + RANGO_MIN;
            write(fd1[WRITE], &number, sizeof(number));
        }

        read(fd2[READ], &contadorPrimo, sizeof(contadorPrimo));
        printf("Los numeros primos suman %d\n", contadorPrimo);

        close(fd2[READ]);
        close(fd1[WRITE]);
    }
    else
    {
        int numero;
        close(fd1[WRITE]);
        close(fd2[READ]);
        while (read(fd1[READ], &numero, sizeof(int)) > 0)
        { // mientras pueda seguir leyendo
            sleep(1);
            if (esPrimo(numero))
            {
                printf("%d\n", numero);
                contadorPrimo += numero;
            }
            else
            {
                printf("%d\n", numero);
            }
            if (multiploDiez(numero))
            {
                kill(padre, SIGUSR1);
                write(fd2[WRITE], &contadorPrimo, sizeof(contadorPrimo));
                break;
            }
        }
    }

    return 0;
}