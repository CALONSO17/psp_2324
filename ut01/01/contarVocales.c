#include<stdio.h>
#include<string.h>
#define CADENA 1024

int main(void){

    char miCadena [CADENA];
    printf("Introduzca una cadena de caracteres:\n");
    fgets(miCadena, CADENA, stdin);

    int cont = 0;
    for (int i = 0; i < strlen(miCadena); i++){

        if(miCadena[i] == 'a' || miCadena[i] == 'e' || miCadena[i] == 'i'  || miCadena[i] == 'o' || miCadena[i] == 'u' ||
            miCadena[i] == 'A' || miCadena[i] == 'E' || miCadena[i] == 'I' || miCadena[i] == 'O' || miCadena[i] == 'U'){
                cont ++;
            }
    }

    printf("La cadena contiene %d vocales\n", cont);
    return 0;
}