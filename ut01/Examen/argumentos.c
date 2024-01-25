#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>   //Para poder poner EXIT_FAILURE
#include <sys/wait.h> //Para incluir wait(NULL)
#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define READ 0
#define WRITE 1

int main()
{

    // El nombre del programa a ejecutar
    char *program = "ip";
    // abajo poner siempre un char mas por el caracter nulo \0 del final, porque si en vez de 3,2 ponia 2,1 me daba error
    char arg1[3] = "ip";
    char arg2[2] = "a";

    int fd1[2];

    if (pipe(fd1) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t id;
    id = fork();

    if (id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (id == 0)
    {
        close(fd1[WRITE]);
        read(fd1[READ], &program, sizeof(program));
        read(fd1[READ], &arg1, sizeof(arg1));
        read(fd1[READ], &arg2, sizeof(arg2));
        // Argumentos para el programa: el nombre del programa, "a" y NULL al final
        char *arguments[] = {arg1, arg2, NULL};
        // Llamar a execvp para ejecutar el comando "ip a"
        execvp(program, arguments);

        // Si execvp falla, imprimirá un error
        perror("execvp");

        close(fd1[READ]);
    }

    close(fd1[READ]);
    // El nombre del programa a ejecutar
    write(fd1[WRITE], &program, sizeof(program));
    write(fd1[WRITE], &arg1, sizeof(arg1));
    write(fd1[WRITE], &arg2, sizeof(arg2));
    close(fd1[READ]);
    wait(NULL);

    return 1;
}

/*#include <sys/types.h>
#include <stdlib.h> //Para poder poner EXIT_FAILURE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //Para incluir wait(NULL)
#include <signal.h> //Para trabajar con señales

int main () {
    char *program = "touch";
    char *arguments [] = {"touch", "archivo.txt", NULL};

    execvp(program, arguments);

    perror("execvp");
    return 1;
}*/