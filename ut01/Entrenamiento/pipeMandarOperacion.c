#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1

int main(){
    pid_t id;
    int num1 = 10;
    int num2 = 2;
    char operacion = '+';// como es un caracter solo con comillas simples
    int resultado;
    int fd1[2]; // Tubería para el hijo

    // Comprobamos si la creación de la tubería tuvo éxito
    if (pipe(fd1) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }

    id = fork();
    if (id == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }else if(id == 0){//hijo
        close(fd1[WRITE]); //cerramos la escritura porque solo vamos a leer
        read(fd1[READ], &num1, sizeof(num1));
        read(fd1[READ], &num2, sizeof(num2));
        read(fd1[READ], &operacion, sizeof(operacion));
        close(fd1[READ]);
        if(operacion == '+'){// la + va con comillas simples porque es un caracter
            resultado = num1 + num2;
        }else if(operacion == '-'){
            resultado = num1 - num2;
        }
        printf("%d\n", resultado);

    }else{//padre
        close(fd1[READ]);//cerramos la lectura porque solo vamos a escribir
        write(fd1[WRITE], &num1, sizeof(num1));
        write(fd1[WRITE], &num2, sizeof(num2));
        write(fd1[WRITE], &operacion, sizeof(operacion));
        close(fd1[WRITE]);

        int status;
        wait(&status);
    }
    return 0;
}