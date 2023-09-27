#include<stdio.h>
int main(void){
    double tempCelsius;
    printf("Introduzca la temperatura en Celsius:\n");
    scanf("%lf", &tempCelsius);
    double tempFar;
    tempFar = (tempCelsius * 9/5) + 32;
    printf("%.2lf Celsius corresponden a %.2lf Fahrenheit\n", tempCelsius, tempFar);
    return 0;
}