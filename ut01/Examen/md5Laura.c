#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>

#define LONG_ALPHABET 26

#define MD5_LEN 16

#define NUM_HASHES 4
#define MD5_LENGTH 33 // Longitud de un hash MD5 (32 caracteres + carácter nulo)

// Función para generar el hash MD5 de una cadena
void generateMD5(const char *string, unsigned char *str_result)
{
    EVP_MD_CTX *ctx;
    const EVP_MD *md;
    unsigned char result[EVP_MAX_MD_SIZE];

    ctx = EVP_MD_CTX_new();
    md = EVP_md5();

    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, string, strlen(string));
    EVP_DigestFinal_ex(ctx, result, NULL);

    EVP_MD_CTX_free(ctx);

    for (int i = 0; i < MD5_LEN; i++)
    { // MD5 result is always 16 bytes
        sprintf(str_result + (i * 2), "%02x", result[i]);
    }
}

// Función para realizar el trabajo del hijo
void realizarTrabajoHIjo(int soy_hijo, int num_proceso)
{
    char hashes[NUM_HASHES][MD5_LENGTH] = {
        "582fc884d6299814fbd4f12c1f9ae70f",
        "74437fabd7c8e8fd178ae89acbe446f2",
        "28ea19352381b8659df830dd6d5c90a3",
        "90f077d7759d0d4d21e6867727d4b2bd"};
    char cadena[5];   // 4 letras+1 de nulo para que sea string
    cadena[4] = '\0'; // siempre sera nulo por lo que lo dejamos aqui
    unsigned char result[EVP_MAX_MD_SIZE];

    // Bucle para probar todas las combinaciones de 4 letras
    for (int i = 0; i < LONG_ALPHABET; i++)
    {
        if (i % num_proceso == soy_hijo)
        {
            cadena[0] = 'a' + i; // es 'a' + i porque de esta forma se encuentra la letra indicada en ASCII
            for (int j = 0; j < LONG_ALPHABET; j++)
            {
                cadena[1] = 'a' + j;
                for (int k = 0; k < LONG_ALPHABET; k++)
                {
                    cadena[2] = 'a' + k;
                    for (int l = 0; l < LONG_ALPHABET; l++)
                    {
                        cadena[3] = 'a' + l;
                        generateMD5(cadena, result);
                        for (int m = 0; m < NUM_HASHES; m++)
                        {
                            if (strcmp(result, hashes[m]) == 0)
                            {
                                printf("Hijo %d encontró hash %d: %s | valor= %s\n", soy_hijo, (m + 1), result, cadena);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("No ha introducido el numero de procesos a usar para el programa %s", argv[0]);
        return 1;
    }

    int n_procesos = atoi(argv[1]);

    pid_t hijos[n_procesos];

    int soy_hijo = 0;

    // Creación de procesos hijos
    for (soy_hijo; soy_hijo < n_procesos; soy_hijo++)
    {
        hijos[soy_hijo] = fork();
        if (hijos[soy_hijo] == 0)
        {
            break;
        }
    }

    // Área de trabajo
    if (soy_hijo == n_procesos)
    { // Soy el padre
        for (int i = 0; i < n_procesos; i++)
        {
            wait(NULL);
        }
    }
    else
    { // Soy hijo
        realizarTrabajoHIjo(soy_hijo, n_procesos);
    }

    return 0;
}
// gcc buscarMd5VariosFork.c -o buscarMd5VariosFork -lssl -lcrypto