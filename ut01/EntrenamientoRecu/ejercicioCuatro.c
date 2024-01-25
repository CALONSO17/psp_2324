/*Crea un programa que reciba un número n por parámetro.
El programa creará n hijos y les enviará una señal a cada uno de ellos para matarlos.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define NUMERO_PARAMETROS 2

int main(int argc, char *argv[])
{
    // Verificar que el número correcto de parámetros fue proporcionado
    if (argc != NUMERO_PARAMETROS)
    {
        printf("Uso: ./ejercicioTres <numero>\n");
        exit(EXIT_FAILURE);
    }

    // Convertir el argumento de línea de comandos a un entero
    int nProcesos = atoi(argv[1]);
    pid_t pid_hijo;

    // Arreglo para almacenar los PID de los hijos
    pid_t hijos[nProcesos];

    // Crear n procesos hijos
    for (int i = 0; i < nProcesos; i++)
    {
        // Crear un nuevo proceso hijo
        pid_t hijo = fork();

        // Verificar errores en la creación del hijo
        if (hijo < 0)
        {
            perror("Error al crear el primer proceso hijo");
            return 1;
        }
        // Proceso hijo
        else if (hijo == 0)
        {
            // Obtener el PID del proceso hijo
            pid_hijo = getpid();

            // Imprimir mensaje del proceso hijo
            printf("He sido creado, soy: %d\n", pid_hijo);
            fflush(stdout); // Vaciar el búfer para asegurar que el mensaje se imprima

            // Ciclo infinito para mantener al proceso hijo en ejecución
            while (1)
            {
                sleep(1);
            }
        }
        // Proceso padre
        else
        {
            // Almacenar el PID del hijo en el arreglo
            hijos[i] = hijo;
        }
    }

    // Esperar 2 segundos antes de enviar señales a los hijos
    sleep(2);

    // Enviar señal SIGKILL a cada hijo y mostrar un mensaje
    for (int i = 0; i < nProcesos; i++)
    {
        printf("Hijo muerto: %d\n", hijos[i]);
        fflush(stdout); // Vaciar el búfer para asegurar que el mensaje se imprima

        // Enviar señal SIGKILL al hijo
        kill(hijos[i], SIGKILL);
    }

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < nProcesos; i++)
    {
        wait(NULL);
    }

    return 0;
}
