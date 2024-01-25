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

#define NUMERO_PARAMETROS 2
#define NUMEROS_COMPROBADOS 99
#define RANGO_NUMEROS 100

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

int main(int argc, char *argv[])
{
    int numInicio = 0;

    if (argc != NUMERO_PARAMETROS)
    {
        printf("Uso: ./ejercicio1 <numero>");
        exit(EXIT_FAILURE);
    }

    int hijos = atoi(argv[1]);

    pid_t arrayHijos[hijos];
    for (int i = 0; i < hijos; i++)
    {
        numInicio += 100;
        arrayHijos[i] = fork();
        if (arrayHijos[i] == 0)
        {
            int contadorNumeros = 0;

            for (int j = numInicio; j < (numInicio + RANGO_NUMEROS); j++)
            {
                if (esPrimo(j))
                {
                    contadorNumeros++;
                    exit(contadorNumeros);
                }
                else
                {
                    contadorNumeros++;
                }
            }
        }
        break;
    }

    for (int i = 0; i < hijos; i++)
    {
        int contadorFinal;
        waitpid(arrayHijos[i], &contadorFinal, 0);

        printf("El hijo %d ha pasado por %d numeros\n", i + 1, WEXITSTATUS(contadorFinal));
    }

    return 0;
}