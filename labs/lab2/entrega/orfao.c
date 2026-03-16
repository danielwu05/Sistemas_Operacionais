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
        printf("Sou o processo pai %d!\n", getpid());
        printf("Sou o pai e vou morrer!\n");
        printf("Criei um filho com PID %d\n", pid);
    }else{
        printf("Filho (PID: %d) - Meu pai inicial era: %d\n", getpid(), getppid());
        sleep(10);
        printf("Filho (PID: %d) - Meu novo pai (adotivo) e: %d\n", getpid(), getppid());
    }
    return 0;
}