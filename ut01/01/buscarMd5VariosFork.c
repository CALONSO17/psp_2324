#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MD5_LEN 16
#define LONGITUD 6

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

int main(void)
{
    unsigned char result[EVP_MAX_MD_SIZE];
    char primeraContrasena[LONGITUD];
    char segundaContrasena[LONGITUD];
    char array[LONGITUD];
    char letras[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 54 letras
    int forks;
    pid_t id;

    printf("¿Cuantos procesos hacen la tarea?\n");
    scanf("%d", &forks);

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (int i = 0; i < forks; i++)
    {
        id = fork();

        if (id < 0)
        {
            perror("Error al crear el proceso hijo");
            return 1;
        }
        else if (id == 0)
        {
            char letraInicial = letras[i];
            char letraFinal = letras[i + 1];

            for (char letra = letraInicial; letra <= letraFinal; letra++)
            {
                array[0] = letra;
                for (int j = 0; j < sizeof(letras) - 1; j++)
                {
                    array[1] = letras[j];
                    for (int k = 0; k < sizeof(letras) - 1; k++)
                    {
                        array[2] = letras[k];
                        for (int l = 0; l < sizeof(letras) - 1; l++)
                        {
                            array[3] = letras[l];
                            for (int m = 0; m < sizeof(letras) - 1; m++)
                            {
                                array[4] = letras[m];
                                array[5] = '\0';
                                generateMD5(array, result);

                                if (strcmp(result, "f4a1c8901a3d406f17af67144a3ec71a") == 0)
                                {
                                    strcpy(primeraContrasena, array);
                                    exit(0);
                                }

                                if (strcmp(result, "d66e29062829e8ae0313adc5a673f863") == 0)
                                {
                                    strcpy(segundaContrasena, array);
                                    exit(0);
                                }
                            }
                        }
                    }
                }
            }
            exit(0);
        }
        else
        {
            // Proceso padre, no hace nada específico aquí
        }
    }

    // Proceso padre espera por los hijos
    for (int i = 0; i < forks; i++)
    {
        wait(NULL);
    }

    printf("Las contraseñas son:\n%s\n%s\n", primeraContrasena, segundaContrasena);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    return 0;
}
// gcc buscarMd5VariosFork.c -o buscarMd5VariosFork -lssl -lcrypto
