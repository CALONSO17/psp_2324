#include<stdio.h>
int main(void){
    int num;
    int i;
    int resultado = 1;

    printf("Dime un número:\n");
    scanf("%d",&num);

    if(num == 0){
        resultado = 1;
    }else if(num<0){
        printf("No se puede hacer el factorial de un número negativo");
    }else{
        for(i=num;i>1;i--){
            resultado *= i;
        }
        printf("El factorial de %d es %d\n", num, resultado);
    }


    return 0;
}