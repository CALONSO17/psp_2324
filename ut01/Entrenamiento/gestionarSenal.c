//Crea un proceso que sea capaz de gestionar un señal definida por el usuario. Luego hará fork y el padre le enviará la señas al hijo. 
//Al gestionar la señal el hijo escribirá "Recibido y terminará el proceso."
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum) {
    // Manejador de señales
    printf("Recibido. Terminando el proceso.\n");
    exit(0);
}

int main() {
    // Establecer el manejador de señales para SIGUSR1
    signal(SIGUSR1, handler);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Código del hijo
        printf("Soy el hijo con PID %d. Esperando la señal...\n", getpid());
        pause(); // Esperar la señal
    } else {
        // Código del padre
        printf("Soy el padre con PID %d. Enviando la señal al hijo %d.\n", getpid(), pid);
        sleep(2); // Espera para que el hijo pueda imprimir su mensaje. El 2 indica que espera 2 segundos
        kill(pid, SIGUSR1); // Enviar la señal SIGUSR1 al hijo
        wait(NULL); // Esperar a que el hijo termine
    }

    return 0;
}






