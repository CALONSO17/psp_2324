
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

#define BASE 10
#define READ 0
#define WRITE 1
#define EXTREMOS_PIPE 2
#define NUMEROS_HIJOS 2
#define BASE_DESPLAZAMIENTO 9
#define NUMERO_PARAMETROS 3
#define NUMEROS_A_ENVIAR 2
#define LONGITUD_NUMERO 1

// Función para determinar si un número es primo
int esPrimo(int numero)
{
    int contador = 2;
    int fin = sqrt(numero);
    bool primo = true;

    int resultado = 0;

    while (contador <= fin && primo)
    {
        if (numero % contador == 0)
        {
            primo = false;
        }
        contador++;
    }

    if (primo)
    {
        resultado = 1;
    }

    return resultado;
}

int main(int argc, char const *argv[])
{
    int salida = EXIT_SUCCESS;

    // Verifica que se hayan proporcionado los parámetros esperados
    if (argc == NUMERO_PARAMETROS)
    {
        // Obtiene los parámetros
        int numerosAEnviar = atoi(argv[NUMEROS_A_ENVIAR]);
        int longitudNumero = atoi(argv[LONGITUD_NUMERO]);

        // Booleano auxiliar para el bucle
        bool seguir = true;

        // Declaración de los pipes
        int pipesHijos[NUMEROS_HIJOS][EXTREMOS_PIPE];

        // Declaración del array para almacenar los identificadores de los hijos
        pid_t hijos[NUMEROS_HIJOS];

        // Contador para los hijos
        int contadorHijos = 0;

        // Contador auxiliar
        int i = 0;

        // Número que se enviará a los hijos y se usará para leer
        int numAEnviar;

        // Crea los pipes y los hijos
        while (contadorHijos < NUMEROS_HIJOS && seguir)
        {
            pipe(pipesHijos[contadorHijos]);
            hijos[contadorHijos] = fork();

            if (hijos[contadorHijos] == 0)
            {
                // Hijo
                seguir = false;
            }
            else
            {
                // Padre
                contadorHijos++;
            }
        }

        // Identificación de quién es quién
        if (seguir)
        {
            // Padre

            // Cierra los pipes de lectura que no se usarán
            while (i < NUMEROS_HIJOS)
            {
                close(pipesHijos[i][READ]);
                i++;
            }

            // Reinicia el contador auxiliar
            i = 0;

            // Genera las bases del número que se desea generar
            int numeroBase = pow(BASE, longitudNumero - 1);
            int modulo = (BASE_DESPLAZAMIENTO * pow(BASE, longitudNumero - 1));

            // Inicializa la semilla para la generación de números aleatorios
            srand(numAEnviar);

            // Bucle para enviar los números a los hijos
            while (i < numerosAEnviar)
            {
                // Genera el número que se va a enviar
                numAEnviar = (rand() % modulo) + numeroBase;

                // Escribe el número en el pipe correspondiente
                write(pipesHijos[i % NUMEROS_HIJOS][WRITE], &numAEnviar, sizeof(numAEnviar));
                i++;
            }

            // Reinicia el contador auxiliar
            i = 0;

            // Cierra los pipes de escritura
            while (i < NUMEROS_HIJOS)
            {
                close(pipesHijos[i][WRITE]);
                i++;
            }

            i = 0;

            // Variable para almacenar la salida del hijo
            int status;

            // Bucle para esperar a que los hijos terminen
            while (i < NUMEROS_HIJOS)
            {
                waitpid(hijos[i], &status, 0);

                // Muestra el resultado de cada hijo
                if (WEXITSTATUS(status) == 0)
                {
                    printf("El hijo %d ha sobrevivido\n", i);
                }
                else
                {
                    printf("El hijo %d no ha sobrevivido\n", i);
                }

                i++;
            }
        }
        else
        {
            // Hijo

            // Cierra el pipe de escritura
            close(pipesHijos[contadorHijos][WRITE]);

            // Variable para indicar si el número debe ser eliminado
            bool eliminacion = false;

            // Cierra los pipes que no son del hijo actual
            while (i < NUMEROS_HIJOS)
            {
                if (i != contadorHijos)
                {
                    close(pipesHijos[i][READ]);
                    close(pipesHijos[i][WRITE]);
                }
                i++;
            }

            // Lee el número que se va a procesar
            while (read(pipesHijos[contadorHijos][READ], &numAEnviar, sizeof(numAEnviar)) > 0)
            {
                printf("Soy el hijo %d y he recibido el número: %d\n", contadorHijos, numAEnviar);

                // Verifica si el número es primo
                if (esPrimo(numAEnviar))
                {
                    eliminacion = true;
                }
            }

            // Determina la salida del hijo
            if (eliminacion)
            {
                exit(EXIT_FAILURE);
            }
            else
            {
                exit(EXIT_SUCCESS);
            }
        }
    }
    else
    {
        // Si no se proporcionan los parámetros esperados, la salida es un error
        salida = EXIT_FAILURE;
    }

    return salida;
}
