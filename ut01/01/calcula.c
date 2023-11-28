#include <stdio.h>   // Incluye la biblioteca estándar de entrada y salida
#include <ctype.h>   // Incluye funciones de manipulación de caracteres
#include <string.h>  // Incluye funciones de manipulación de cadenas
#include <stdlib.h>  // Incluye funciones de conversión de cadenas a números

int main(int argc, char *argv[]) {

    // Verifica si el número de argumentos es diferente de 4
    if (argc != 4) {
        printf("ERROR: Se esperan 4 argumentos\n");
        return 1;
    }

    // Convierte los argumentos de cadena a números de punto flotante
    double num1 = atof(argv[2]);
    double num2 = atof(argv[3]);
    double resultado = 0;

    // Comprueba el tipo de operación especificada en el primer argumento
    if (strcmp(argv[1], "suma") == 0) {
        resultado = num1 + num2;
    } else if (strcmp(argv[1], "resta") == 0) {
        resultado = num1 - num2;
    } else if (strcmp(argv[1], "multiplica") == 0) {
        resultado = num1 * num2;
    } else if (strcmp(argv[1], "divide") == 0) {
        // Verifica si se está intentando dividir por cero
        if (num2 == 0) {
            printf("No puedes dividir entre 0\n");
            return 1;
        }
        resultado = num1 / num2;
    }

    // Imprime el resultado con dos decimales
    printf("%.2lf\n", resultado);

    return 0;  // Indica que el programa terminó correctamente
}