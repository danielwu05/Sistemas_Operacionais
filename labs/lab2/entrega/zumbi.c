#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar um novo processo!\n");
        return 1;
    }
    if (pid > 0) {
        printf("Sou o processo pai %d e meu filho é %d\n", getpid(), pid);
        sleep(60);
    }else{
        sleep(5);
        printf("Filho zumbi\n");
    }
    return 0;
}