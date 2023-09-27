#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int main(void){
    int num;
    bool primo = true;
    printf("Indroduzca un número:\n");
    scanf("%d",&num);
    int i = 2;

    if(num<=1){
        primo = false;
    }

    while(primo && i<= sqrt(num)){
        if(num % i == 0){
            primo = false;
        }
        i++;
    }

    if(primo){
        printf("Es primo\n");
    }else
        printf("No es primo\n");
    return 0;
}