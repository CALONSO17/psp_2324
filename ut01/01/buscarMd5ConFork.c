#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include<unistd.h>
#include<sys/types.h>
#include <time.h>

#define MD5_LEN 16
#define LONGITUD 6

void generateMD5(const char *string, unsigned char *str_result) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;
    unsigned char result[EVP_MAX_MD_SIZE];

    ctx = EVP_MD_CTX_new();
    md = EVP_md5();

    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, string, strlen(string));
    EVP_DigestFinal_ex(ctx, result, NULL);

    EVP_MD_CTX_free(ctx);

    for(int i = 0; i < MD5_LEN; i++){   // MD5 result is always 16 bytes
        sprintf(str_result+(i*2),"%02x", result[i]);
    }
}

int main(void){

    unsigned char result[EVP_MAX_MD_SIZE];
    char primeraContrasena[LONGITUD];
    char segundaContrasena[ LONGITUD];
    char array[LONGITUD];
    char primeraLetra;
    char segundaLetra;
    char terceraLetra;
    char cuartaLetra;
    char quintaLetra;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    pid_t id;
    id = fork();
    

    if(id != 0){
        for(int i = 65; i <= 90; i++){
            primeraLetra= (char)i;

            for(int i = 65; i <= 122; i++){
                segundaLetra= (char)i;

                for(int i = 65; i <= 122; i++){
                    terceraLetra= (char)i;

                    for(int i = 65; i <= 122; i++){
                        cuartaLetra= (char)i;

                        for(int i = 65; i <= 122; i++){
                            quintaLetra = (char)i;
                            array[0] = primeraLetra;
                            array[1] = segundaLetra;
                            array[2] = terceraLetra;
                            array[3] = cuartaLetra; 
                            array[4] = quintaLetra;
                            array[5] = '\0';
                            generateMD5(array, result);
                            //printf("MD5(\"%s\") = %s\n", array, result);

                            if(strcmp(result, "f4a1c8901a3d406f17af67144a3ec71a") == 0){
                                strcpy(primeraContrasena, array);
                            }

                            if(strcmp(result, "d66e29062829e8ae0313adc5a673f863") == 0){
                                strcpy(segundaContrasena, array);
                            }
                        }
                    }
                }           
            }
        }
        wait();//un wait por cada hijo creado
    }else{
        for(int i = 90; i <= 122; i++){
            primeraLetra= (char)i;

            for(int i = 65; i <= 122; i++){
                segundaLetra= (char)i;

                for(int i = 65; i <= 122; i++){
                    terceraLetra= (char)i;

                    for(int i = 65; i <= 122; i++){
                        cuartaLetra= (char)i;

                        for(int i = 65; i<=122; i++){
                            quintaLetra = (char)i;
                            array[0] = primeraLetra;
                            array[1] = segundaLetra;
                            array[2] = terceraLetra;
                            array[3] = cuartaLetra; 
                            array[4] = quintaLetra;
                            array[5] = '\0';
                            generateMD5(array, result);
                            //printf("MD5(\"%s\") = %s\n", array, result);

                            if(strcmp(result, "f4a1c8901a3d406f17af67144a3ec71a") == 0){
                                strcpy(primeraContrasena, array);
                            }

                            if(strcmp(result, "d66e29062829e8ae0313adc5a673f863") == 0){
                                strcpy(segundaContrasena, array);
                            }
                        }
                    }
                }           
            }
        }
    }

    
    printf("Las contraseñas son:\n%s\n%s\n",primeraContrasena, segundaContrasena);
    end = clock(); 
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    return 0;
}