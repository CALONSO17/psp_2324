/*El manejo de ficheros en C es una parte importante de la programación, ya que permite a los programas interactuar con archivos e
n el sistema de archivos. Aquí te presento los conceptos básicos relacionados con el manejo de ficheros en C:

Puntero a archivo (FILE*): En C, se utiliza el tipo FILE* para declarar punteros a archivos. Estos punteros se utilizan 
para abrir, leer, escribir y manipular archivos. Debes incluir la biblioteca <stdio.h> para trabajar con archivos.

Apertura de archivos: Para abrir un archivo, se utiliza la función fopen(). Puedes abrir archivos en modo lectura ("r"), escritura ("w"), 
apertura para añadir datos ("a"), etc. Por ejemplo:*/

FILE* archivo;
archivo = fopen("archivo.txt", "r");
if (archivo == NULL) {
    perror("No se pudo abrir el archivo");
    return 1;
}
/*Lectura y escritura de archivos: Para leer desde un archivo, puedes utilizar las funciones fread() o fgets(). 
Para escribir en un archivo, se usa fwrite() o fprintf(). Ejemplo de lectura y escritura:*/

char buffer[100];
// Leer una línea del archivo
fgets(buffer, sizeof(buffer), archivo);
// Escribir en el archivo
fprintf(archivo, "Datos a escribir en el archivo\n");
//Cierre de archivos: Siempre es importante cerrar los archivos después de trabajar con ellos para liberar recursos. Usa la función fclose():

fclose(archivo);
/*Comprobación de errores: Es fundamental verificar si las operaciones de apertura, lectura o escritura de 
archivos tienen éxito. Puedes hacerlo comprobando si el puntero al archivo es NULL o utilizando la función ferror().*/

if (archivo == NULL) {
    perror("No se pudo abrir el archivo");
    return 1;
}
/*Manejo de archivos binarios y de texto: Puedes trabajar tanto con archivos de texto como con archivos binarios. 
Los archivos de texto almacenan datos legibles por humanos, mientras que los archivos binarios almacenan datos en 
su forma cruda. El modo de apertura ("r", "rb", "w", "wb", etc.) determina si el archivo se maneja como texto o binario.*/

//Ejemplo de texto
#include <stdio.h>
#define BUFFER_SIZE 100

int main() {
    // Abrir el archivo en modo escritura de texto
    FILE* archivo = fopen("datos.txt", "w");

    // Comprobar si se pudo abrir el archivo
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Escribir líneas de texto en el archivo
    fprintf(archivo, "Hola, mundo!\n");
    fprintf(archivo, "Este es un archivo de texto.\n");

    // Cerrar el archivo
    fclose(archivo);

    // Abrir el archivo en modo lectura de texto
    archivo = fopen("datos.txt", "r");

    // Comprobar si se pudo abrir el archivo
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Leer y mostrar las líneas de texto desde el archivo
    printf("Leyendo el archivo de texto:\n");
    char linea[BUFFER_SIZE];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    // Cerrar el archivo
    fclose(archivo);

    return 0;
}
Ejemplo binario
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_LENGTH 50

struct Registro {
    int numero;
    char nombre[NOMBRE_LENGTH];
};

int main() {
    // Declarar una estructura para almacenar datos
    struct Registro datos;

    // Abrir el archivo en modo escritura binaria
    FILE* archivo = fopen("datos.bin", "wb");

    // Comprobar si se pudo abrir el archivo
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Escribir datos en el archivo
    datos.numero = 65;
    strcpy(datos.nombre, "Ejemplo 1");
    fwrite(&datos, sizeof(struct Registro), 1, archivo);

    datos.numero = 169;
    strcpy(datos.nombre, "Ejemplo 2");
    fwrite(&datos, sizeof(struct Registro), 1, archivo);

    // Cerrar el archivo
    fclose(archivo);

    // Abrir el archivo en modo lectura binaria
    archivo = fopen("datos.bin", "rb");

    // Comprobar si se pudo abrir el archivo
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Leer datos desde el archivo
    printf("Leyendo datos del archivo:\n");
    while (fread(&datos, sizeof(struct Registro), 1, archivo) == 1) {
        printf("Número: %d, Nombre: %s\n", datos.numero, datos.nombre);
    }

    // Cerrar el archivo
    fclose(archivo);

    return 0;
}