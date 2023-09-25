#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){
    pid_t id;

    int n =42;
    double pi = 3.14;

    //clonacion
    id = fork();

    //Hay dos procesos
    if(id != 0){
        printf("Soy el padre , mi id es %d, y mi hijo es %d\n",getpid(), id);
        n = 1000;
    }else{
        printf("Soy el hijo, mi id es %d, y mi hijo es %d\n", getpid(), id);
        printf("N vale %d\n", n);
    }

    return 0;
}