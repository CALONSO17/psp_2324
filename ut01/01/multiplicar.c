#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    int status;

    int resultado;
    pid_t idHijo;

    for(int i = 1; i < 10; i++){
        idHijo = fork();
        if(idHijo == 0){
            printf("Tabla de multiplicar %d\n", i);
            for(int j = 1; j < 10; j++){
                resultado = i * j;
                printf("%d x %d = %d\n",i,j,resultado);
            }
            exit(0);
        }
    }

    
    for (int i = 0; i < 10; i++){
        wait(&status);
    }
}