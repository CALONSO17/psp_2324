/*5. Crea un proceso que sea capaz de gestionar un señal definida por el usuario. Luego hará fork y el padre
le enviará la señal al hijo. Al gestionar la señal el hijo escribirá "Recibido y terminará el proceso."*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

// Usar un booleano en lugar de sig_atomic_t
bool señal_recibida = false;

// Manejador de señales
void manejadorSeñal(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("Hijo: Señal recibida y terminando el proceso.\n");
        señal_recibida = true;
    }
}

int main()
{
    pid_t pid_hijo;

    // Configurar el manejador de señales para el proceso hijo (aunque tambien en padre)
    signal(SIGUSR1, manejadorSeñal);

    // Crear un nuevo proceso hijo
    pid_hijo = fork();

    if (pid_hijo < 0)
    {
        // Error al crear el proceso hijo
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }
    else if (pid_hijo == 0)
    { // Soy hijo

        // Esperar a que el padre le envíe la señal
        while (!señal_recibida)
        {
            sleep(1);
        }

        // Terminar proceso hijo
        exit(EXIT_SUCCESS);
    }
    else
    { // Soy padre

        // Enviar la señal al hijo
        printf("Padre: Enviando señal al hijo.\n");
        kill(pid_hijo, SIGUSR1);

        // Esperar a que el hijo termine
        wait(NULL);

        printf("Padre: El hijo ha terminado.\n");
    }

    return 0;
}
