
/*Redirección
La función dup2 en sistemas operativos basados en UNIX se utiliza para duplicar un descriptor de archivo existente a
 otro descriptor de archivo. Lo que hace es "redirigir" la entrada, salida o errores de un proceso a otra ubicación.
 Puede ser útil en situaciones como cuando quieres que un proceso escriba su salida no en la terminal (que es su comportamiento predeterminado), 
 sino en un archivo.

Funcionamiento de dup2: La función tiene esta forma:*/

int dup2(int oldfd, int newfd);
/*Parámetros:

oldfd: Es el descriptor de archivo original que ya está abierto y que quieres duplicar.
newfd: Es el descriptor de archivo al que quieres redirigir oldfd. Si newfd ya estaba abierto, dup2 lo cerrará antes de hacer la redirección.`*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Abrir un archivo para escritura
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("open");
        return 1;
    }

    // Redirigir la salida estándar al archivo
    dup2(file, STDOUT_FILENO);  // STDOUT_FILENO es una constante que representa la salida estándar

    // Ahora, cualquier cosa que escribamos usando printf irá al archivo "output.txt"
    printf("¡Hola, mundo!");

    // Cerrar el archivo
    close(file);

    return 0;
}