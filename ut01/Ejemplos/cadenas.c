/*En C, una cadena es una secuencia de caracteres terminada por un carácter nulo ('\0'). Los caracteres en una 
cadena pueden ser letras, números, símbolos u otros caracteres especiales. Las cadenas en C son representadas como arrays de caracteres,
 donde cada carácter se almacena en un elemento del array y el carácter nulo ('\0') marca el final de la cadena.

Declaración y asignación de cadenas:*/

char miCadena[] = "Hola, mundo!";  //Longitud 13
char miCadena[12] = "Hola, mundo!";//No entra. Falta un espacio para el \0
#include <stdio.h>

int main() {
    char miCadena[] = "Hola, mundo!";
    printf("%s\n", miCadena);
    return 0;
}
#include <stdio.h>
#include <string.h>

int main() {
    char miCadena[] = "Hola, mundo!";
    int longitud = strlen(miCadena);
    printf("Longitud de la cadena: %d\n", longitud);
    return 0;
}
#include <stdio.h>
#include <string.h>

int main() {
    char cadena1[] = "Hola";
    char cadena2[] = "Hola";

    if (strcmp(cadena1, cadena2) == 0) {
        printf("Las cadenas son iguales.\n");
    } else {
        printf("Las cadenas son diferentes.\n");
    }

    return 0;
}
¡//OJO! Hay comillas simples y comillas dobles.

char cadena[] = "Esto es una cadena";
char letra = cadena[3];
if(letra == 'o') {
    printf("Entiendo la diferencia entre cadena y caracter");
}