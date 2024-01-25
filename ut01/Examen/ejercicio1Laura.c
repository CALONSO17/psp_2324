#include <sys/types.h>
#include <stdlib.h> //Para poder poner EXIT_FAILURE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Para incluir wait(NULL)
#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define READ 0
#define WRITE 1

#define NUMERO_PARAMETROS 3 // 2 argumentos +1 del nombre

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
    if (argc != NUMERO_PARAMETROS)
    {
        printf("Uso: %s <argumentos insufcientes >\n", argv[0]);
        return 1;
    }

    int longitud_num = atoi(argv[1]);
    int cant_nums = atoi(argv[2]);

    if (longitud_num <= 0)
    {
        printf("La longitud del numero debe ser 1 o mayor.\n");
        return 1;
    }

    if (cant_nums <= 0)
    {
        printf("Debe pasar al menos un numero aleatorio.\n");
        return 1;
    }

    // Creamos pipes uno para cada hijo
    int pipe_fd1[2], pipe_fd2[2];

    if (pipe(pipe_fd1) == -1)
    {
        perror("Error al crear la primera tubería ");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe_fd2) == -1)
    {
        perror("Error al crear la segunda tubería");
        exit(EXIT_FAILURE);
    }

    // Crear el proceso hijo1
    pid_t id_hijo1 = fork();

    if (id_hijo1 == -1)
    {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }

    if (id_hijo1 == 0)
    {                           // soy primer hijo
        close(pipe_fd1[WRITE]); // Cerrar el extremo de escritura del proceso hijo1

        // Cerramos por completo el pipe que no estamos usando en este hijo
        close(pipe_fd2[WRITE]);
        close(pipe_fd2[READ]);

        // Leer los números desde la tubería, uno a uno e imprimir inmediatamente
        bool primoEncontrado = false;
        int numero;
        while (read(pipe_fd1[READ], &numero, sizeof(int)) > 0)
        { // mientras pueda seguir leyendo
            if (esPrimo(numero))
            {
                printf("Soy el hijo1 y he recibido %d : es primo\n", numero);
                primoEncontrado = true;
            }
            else
            {
                printf("Soy el hijo1 y he recibido %d : NO es primo\n", numero);
            }
        }

        exit(primoEncontrado);
    }

    pid_t id_hijo2 = fork();

    if (id_hijo2 == -1)
    {
        perror("Error al crear el segundo hijo");
        exit(EXIT_FAILURE);
    }

    if (id_hijo2 == 0)
    { // soy el segundo hijo

        close(pipe_fd2[WRITE]); // Cerrar el extremo de escritura del proceso hijo2

        // Cerramos por completo el pipe que no estamos usando en este hijo
        close(pipe_fd1[READ]);
        close(pipe_fd1[WRITE]);

        // Leer los números desde la tubería, uno a uno e imprimir inmediatamente
        bool primoEncontrado = false;
        int numero;
        while (read(pipe_fd2[READ], &numero, sizeof(int)) > 0)
        { // mientras pueda seguir leyendo
            if (esPrimo(numero))
            {
                printf("Soy el hijo2 y he recibido %d : es primo\n", numero);
                primoEncontrado = true;
            }
            else
            {
                printf("Soy el hijo2 y he recibido %d : NO es primo\n", numero);
            }
        }

        exit(primoEncontrado);
    }

    // soy padre

    // Cerrar los extremos de lectura de la tubería en el proceso padre, en ambos hijos
    close(pipe_fd1[READ]);
    close(pipe_fd2[READ]);

    srand(time(NULL)); // esto es para que sea otra semilla y asi los numeros cambien en cada ejecucion

    for (int i = 0; i < cant_nums; i++)
    {
        // Creamos numeros aleatorios segun la longitud de num REVISAR==============================================
        int numeroHijo1 = (rand() % 10 ^ longitud_num) + 1;
        int numeroHijo2 = (rand() % 10 ^ longitud_num) + 1;

        // enviamos el mismo numero a ambos hijos
        write(pipe_fd1[WRITE], &numeroHijo1, sizeof(int));
        write(pipe_fd2[WRITE], &numeroHijo2, sizeof(int));
    }
    // Cerrar las tuberias al fin
    close(pipe_fd1[WRITE]);
    close(pipe_fd2[WRITE]);
    // Variables en los que esta el estado
    int encontradoPrimo1;
    int encontradoPrimo2;

    waitpid(id_hijo1, &encontradoPrimo1, 0);
    waitpid(id_hijo2, &encontradoPrimo2, 0);

    if (WEXITSTATUS(encontradoPrimo1) == true)
    {
        printf("El hijo1 ha encontrado un primo. MUERTE\n");
    }
    else
    {
        printf("El hijo1 no ha encontrado ningun primo. ¡SALVADO!\n");
    }

    if (WEXITSTATUS(encontradoPrimo2) == true)
    {
        printf("El hijo2 ha encontrado un primo. MUERTE\n");
    }
    else
    {
        printf("El hijo2 no ha encontrado ningun primo. ¡SALVADO!\n");
    }

    return 0;
}