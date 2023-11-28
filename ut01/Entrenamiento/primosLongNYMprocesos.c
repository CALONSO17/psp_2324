//Crea un programa en c que reciba un número n y un número m. El programa escribirá todos los números primos de la longitud n, utilizando m procesos.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

// Función para verificar si un número es primo
int esPrimo(int numero) {
    if (numero <= 1) {
        return 0; // Números menores o iguales a 1 no son primos
    }
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            return 0; // El número no es primo
        }
    }
    return 1; // El número es primo
}

// Función que realiza el trabajo de cada proceso hijo
void realizarTrabajoDeHijo(int soy_hijo, int n_procesos, int nIntroducido) {
    // Calcular el rango para este proceso hijo
    int rangoInicio = soy_hijo * (nIntroducido / n_procesos) + 1;
    int rangoFin = (soy_hijo + 1) * (nIntroducido / n_procesos);

    // Si soy el último proceso hijo, ajustar el rangoFin
    if (soy_hijo == n_procesos - 1) {
        rangoFin += nIntroducido % n_procesos;
    }

    // Buscar números primos en mi rango asignado
    for (int i = rangoInicio; i <= rangoFin; i++) {
        if (esPrimo(i)) {
            // Imprimir el número primo junto con el número de proceso al que pertenece
            printf("Proceso %d: El numero %d es primo\n", soy_hijo, i);
        }
    }
}

int main() {
    int n_procesos;
    int nIntroducido;

    // Solicitar al usuario que introduzca la longitud de los números primos (n)
    printf("Introduce la longitud de los numeros primos (n): \n");
    scanf("%d", &nIntroducido);

    // Solicitar al usuario que introduzca el número de procesos (m)
    printf("Introduce el numero de procesos (m): \n");
    scanf("%d", &n_procesos);

    // Arreglo para almacenar los identificadores de los procesos hijos
    pid_t id_hijos[n_procesos];

    // Crear procesos hijos
    for (int soy_hijo = 0; soy_hijo < n_procesos; soy_hijo++) {
        id_hijos[soy_hijo] = fork();

        // Verificar si soy el proceso hijo
        if (id_hijos[soy_hijo] == 0) {
            // Soy un proceso hijo, realizar mi trabajo y salir
            realizarTrabajoDeHijo(soy_hijo, n_procesos, nIntroducido);
            exit(0);
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < n_procesos; i++) {
        wait(NULL);
    }

    return 0;
}




// para ejecutar gcc primosLongNYMprocesos.c -o primosLongNYMprocesos -lm
