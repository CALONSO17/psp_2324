#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    // Abrir un archivo para escritura
    int file = open("contenido_directorio.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("open");
        return 1;
    }

    // Redirigir la salida estándar al archivo
    dup2(file, STDOUT_FILENO);

    // Abrir el directorio raíz
    DIR *dir = opendir("/");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Leer y escribir el contenido del directorio
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Cerrar el directorio y el archivo
    closedir(dir);
    close(file);

    return 0;
}