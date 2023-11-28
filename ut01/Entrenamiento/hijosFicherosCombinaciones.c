// Crea un programa que reciba por parámetro un número entero positivo n. Este número indicará el número de hijos. 
//Cada hijo generará un fichero con la posibles combinación de caracteres de esa longitud. 
//El hijo 1 una letra, el hijo 2 dos letras 'aa' a la 'zz', etc. Los nombres serán datos1.txt, datos2.txt, etc.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

int main() {
    int hijos;
    scanf("%d", &hijos);

    pid_t id;

    // Iterar para crear la cantidad de procesos hijos especificada
    for (int i = 0; i < hijos; i++) {
        id = fork(); // Crear un nuevo proceso hijo

        if (id == 0) { // Verificar si es el proceso hijo
            char nombreArchivo[20];
            // Construir el nombre del archivo con formato "datosX.txt"
            snprintf(nombreArchivo, sizeof(nombreArchivo), "datos%d.txt", i + 1);

            FILE *archivo = fopen(nombreArchivo, "w"); // Abrir archivo en modo escritura

            if (archivo == NULL) {
                perror("No se pudo abrir el archivo");
                return 1;
            }

            // Escribir en el archivo
            for (int j = 97; j <= 122; j++) {
                for(int k = 0; k < i + 1; k++){// esto lo hago para que añada una letra mas por cada hijo
                    fprintf(archivo, "%c", (char)j);
                }
                fprintf(archivo, "\n");
            }

            // Cerrar el archivo
            fclose(archivo);
            
            break; // Salir del bucle en el proceso hijo
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < hijos; i++) {
        wait(NULL);
    }

    return 0;
}