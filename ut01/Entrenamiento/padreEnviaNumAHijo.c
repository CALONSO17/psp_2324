#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define MAX 100

int main(){

    srand(time(NULL));
    pid_t id;
    int num1, num2, num3;

    FILE* archivo = fopen("salida.txt", "w");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    id = fork();
    
    if(id != 0){

        num1 = rand() % MAX;
        num2 = rand() % MAX;
        num3 = rand() % MAX;

        close(fd[READ]);
        write(fd[WRITE], &num1, sizeof(num1));
        write(fd[WRITE], &num2, sizeof(num2));
        write(fd[WRITE], &num3, sizeof(num3));
        close(fd[WRITE]);

        int status;
        wait(&status);

    }else{

        read(fd[READ], &num1, sizeof(num1));
        read(fd[READ], &num2, sizeof(num2));
        read(fd[READ], &num3, sizeof(num3));
        close(fd[READ]);

        if (num1 > num2) {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }
        
        if (num2 > num3) {
            int temp = num2;
            num2 = num3;
            num3 = temp;
        }
        
        if (num1 > num2) {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        fprintf(archivo, "%d", num1);
        fprintf(archivo, "%d", num2);
        fprintf(archivo, "%d", num3);
        fclose(archivo);

    }

    return 0;
}