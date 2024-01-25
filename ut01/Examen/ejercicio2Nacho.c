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

#define BUFFER 1024
int contadorSenales = 0;

// Manejador de la señal SIGUSR1
void handlerSigusr(int senal)
{
    if (contadorSenales == 0)
    {
        contadorSenales++;
        printf("Soy el hijo %d y llevo %d señales\n", getpid(), contadorSenales);
    }
    else
    {
        contadorSenales++;
        printf("Soy el hijo %d y he sido eliminado otra vez, llevo %d señales\n", getpid(), contadorSenales);
    }
}

// Manejador de la señal SIGINT
void handlerSigint(int senal)
{
    printf("Soy el hijo %d y termino\n", getpid());
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    int hijoDestino;
    int cantidadProcesosHijos = atoi(argv[1]);
    int numeroSenales = atoi(argv[2]);
    pid_t conjuntoHijos[cantidadProcesosHijos];

    // Crear procesos hijos
    for (int i = 0; i < cantidadProcesosHijos; i++)
    {
        conjuntoHijos[i] = fork();

        if (conjuntoHijos[i] == 0)
        {
            // Código ejecutado por los hijos

            // Configurar manejadores de señales
            signal(SIGUSR1, handlerSigusr);
            signal(SIGINT, handlerSigint);

            // Bucle infinito para que los hijos esperen señales
            while (1)
            {
                sleep(1);
            }

            // Esta línea nunca se ejecutará debido al bucle infinito, pero se deja por claridad
            exit(EXIT_SUCCESS);
        }
    }

    // Imprimir los PID de los hijos creados
    for (int i = 0; i < cantidadProcesosHijos; i++)
    {
        printf("%d\n", conjuntoHijos[i]);
    }
    sleep(3);
    // Enviar señales a los hijos de forma aleatoria
    for (int i = 0; i < numeroSenales; i++)
    {
        hijoDestino = rand() % cantidadProcesosHijos;
        kill(conjuntoHijos[hijoDestino], SIGUSR1);
        sleep(4);
    }

    // Enviar señal de terminación (SIGINT) a todos los hijos
    for (int i = 0; i < cantidadProcesosHijos; i++)
    {
        kill(conjuntoHijos[i], SIGINT);
    }

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < cantidadProcesosHijos; i++)
    {
        wait(NULL);
    }

    return 0;
}
