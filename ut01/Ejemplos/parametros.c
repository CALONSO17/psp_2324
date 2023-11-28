/* pasados en la línea de comandos. Cada elemento del array apunta a una cadena que contiene un argumento. 
El primer elemento (argv[0]) siempre es una cadena que contiene el nombre del programa en sí, y los argumentos adicionales se almacenan 
en los elementos subsiguientes (argv[1], argv[2], etc.).

A continuación, te muestro un ejemplo de cómo se utilizan argc y argv en la función main():*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    // El primer argumento (argv[0]) es el nombre del programa
    printf("Nombre del programa: %s\n", argv[0]);

    // Verificar si se proporcionaron argumentos adicionales
    if (argc > 1) {
        printf("Argumentos adicionales:\n");
        // Recorrer los argumentos adicionales y mostrarlos
        for (int i = 1; i < argc; i++) {
            printf("Argumento %d: %s\n", i, argv[i]);
        }
    } else {
        printf("No se proporcionaron argumentos adicionales.\n");
    }

    return 0;
}
/*En este ejemplo, argc contendrá el número total de argumentos (incluyendo el nombre del programa) y 
argv será un array de punteros a las cadenas que representan esos argumentos. Puedes acceder a los argumentos individuales 
utilizando los índices en argv. Si no se proporcionan argumentos adicionales, el programa mostrará un mensaje
 indicando que no se proporcionaron argumentos adicionales.*/