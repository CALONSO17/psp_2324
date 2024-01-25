/*Crea un programa que reciba por parámetro un número entero positivo n. Este número indicará el número de hijos.
Cada hijo generará un fichero con la posibles combinación de caracteres de esa longitud. El hijo 1 una letra,
el hijo 2 dos letras 'aa' a la 'zz', etc. Los nombres serán datos1.txt, datos2.txt, etc.*/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define NUMERO_PARAMETROS 2

int main(int argc, char *argv[])
{
    if (argc != NUMERO_PARAMETROS)
    {
        printf("Uso: ./ejercicioTres <numero>");
        exit(EXIT_FAILURE);
    }

    int hijos = atoi(argv[1]);
    int num;
    char nombre[20];

    pid_t id;
    for (int i = 0; i < hijos; i++)
    {
        id = fork();
        if (id == 0)
        {
            num = i + 1;
            sprintf(nombre, "datos%d.txt", num); // Utilizamos sprintf para formatear el nombre del archivo.
            FILE *archivo;
            archivo = fopen(nombre, "w");
            // Escribir en el archivo
            int base = 'a';
            for (int j = 0; j < 26; j++)
            {
                for (int k = 0; k < i + 1; k++)
                {
                    fprintf(archivo, "%c", (char)(base + j));
                }
                fprintf(archivo, "\n");
            }
            break;
        }
    }

    for (int i = 0; i < hijos; i++)
    {
        wait(NULL);
    }
}