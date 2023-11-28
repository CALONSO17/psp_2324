#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define MD5_LEN 16
#define LONGITUD 5

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
    char terceraContrasena[LONGITUD];
    char cuartaContrasena[LONGITUD];
    char array[LONGITUD];
    char primeraLetra;
    char segundaLetra;
    char terceraLetra;
    char cuartaLetra;
    
    for(int i = 97; i <= 122; i++){
        primeraLetra= (char)i;

        for(int i = 97; i <= 122; i++){
            segundaLetra= (char)i;

            for(int i = 97; i <= 122; i++){
                terceraLetra= (char)i;

                for(int i = 97; i <= 122; i++){
                    cuartaLetra= (char)i;
                    array[0] = primeraLetra;
                    array[1] = segundaLetra;
                    array[2] = terceraLetra;
                    array[3] = cuartaLetra; 
                    array[4] = '\0';
                    generateMD5(array, result);
                    //printf("MD5(\"%s\") = %s\n", array, result);

                    if(strcmp(result, "582fc884d6299814fbd4f12c1f9ae70f") == 0){
                        strcpy(primeraContrasena, array);
                    }

                    if(strcmp(result, "74437fabd7c8e8fd178ae89acbe446f2") == 0){
                        strcpy(segundaContrasena, array);
                    }

                    if(strcmp(result, "28ea19352381b8659df830dd6d5c90a3") == 0){
                        strcpy(terceraContrasena, array);
                    }

                    if(strcmp(result, "90f077d7759d0d4d21e6867727d4b2bd") == 0){
                        strcpy(cuartaContrasena, array);
                    }
                    
                }
            }
                    
        }
    }
    printf("Las contraseñas son:\n%s\n%s\n%s\n%s\n",primeraContrasena, segundaContrasena,terceraContrasena,cuartaContrasena);

    return 0;
}