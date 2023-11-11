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
    int fd2[2];

    // Comprobamos si la creación de la tubería tuvo éxito
    if (pipe(fd1) == -1 || pipe(fd2)) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }

    id = fork();
    if (id == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }else if(id == 0){//hijo
        close(fd1[WRITE]); //cerramos la escritura porque solo vamos a leer
        close(fd2[READ]);//cerramos la lectura del segundo pipe porque solo queremos enviar el resultado

        read(fd1[READ], &num1, sizeof(num1));
        read(fd1[READ], &num2, sizeof(num2));
        read(fd1[READ], &operacion, sizeof(operacion));
        
        close(fd1[READ]);
        

        if(operacion == '+'){// la + va con comillas simples porque es un caracter
            resultado = num1 + num2;
        }else if(operacion == '-'){
            resultado = num1 - num2;
        }
        write(fd2[WRITE], &resultado, sizeof(resultado));
        close(fd2[WRITE]);

    }else{//padre
        close(fd1[READ]);//cerramos la lectura porque solo vamos a escribir
        close(fd2[WRITE]);//cerramos la escritura del pipe 2 porque solo vamos a recibir el resultado

        write(fd1[WRITE], &num1, sizeof(num1));
        write(fd1[WRITE], &num2, sizeof(num2));
        write(fd1[WRITE], &operacion, sizeof(operacion));

        close(fd1[WRITE]);

        read(fd2[READ], &resultado, sizeof(resultado));
        printf("Soy el padre, el resultado es %d\n", resultado);
        close(fd2[READ]);

        int status;
        wait(&status);
    }
    return 0;
}