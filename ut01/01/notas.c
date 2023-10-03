#include<stdio.h>
#define NOTAS 5

int main(void){
    double notas [NOTAS];
    double nota;
    double notaBaja = 10;
    double notaAlta = 0;
    double media = 0;

    int longitud = NOTAS;

    for(int i = 0; i< longitud; i++){
        printf("Añade una nota\n");
        scanf("%lf",&nota);
        notas[i] = nota;

        if(nota < notaBaja){
            notaBaja = nota;
        }

        if(nota > notaAlta){
            notaAlta = nota;
        }

        media += nota;

    }

    for(int i = 0; i < longitud; i++){
        printf("%.2lf = ", notas[i]);
        if(notas[i] < 5){
            printf("Has suspendido\n");
        }else
            printf("Has aprobado\n");
    }

    printf("la nota media es: %.2lf\n", media/NOTAS);
    printf("La nota mas alta es: %2.lf\n", notaAlta);
    printf("La nota mas baja es: %.2lf\n", notaBaja);

    return 0;
}