#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define MICADENA 1024

int main(void){
    char  frase [MICADENA];
    bool esPalindromo = true;

    printf("---PALINDROMO---\n");
    printf("Introduzca un texto:\n");
    fgets(frase, MICADENA, stdin);

    int longitud = strlen(frase);

    for(int i = 0, j = longitud -1; i < j; i++, j--){
        while(isspace(frase[i])){
            i++;
        }
        while(isspace(frase[j])){
            j--;
        }
        if(tolower(frase[i]) != tolower(frase[j])){
                esPalindromo = false;
            }
            
    }

    if (esPalindromo == true){
        printf("Es palíndromo\n");
    }else
        printf("No es palíndromo\n");

    return 0;
}