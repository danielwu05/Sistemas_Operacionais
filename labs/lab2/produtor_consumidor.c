/*
    1. O pai prepara o ambiente criando a memória compartilhada e mapeando o seu
    conteúdo (shm_open, ftruncate e mmap).
    shm_fd = shm_open(name, O_RDONLY, 0666);

    2. O pai cria um processo filho com fork()
    pid_t pid = fork();

    3. No processo filho, a memória compartilhada é acessada pelo ponteiro para ser
    escrita com sprintf. Você pode escrever aqui a mensagem que quiser.
    sprintf(ptr, "%s", message_0);

    4. O filho deve então encerrar sua execução
    exit(0)

    
    5. No pai, você deve esperar o filho concluir seu trabalho. Caso contrário, o pai
    executará sem que o filho tenha produzido na memória compartilhada.
    wait(5)

    6. Depois, o pai deve consumir o conteúdo produzido pelo filho usando um
    printf comum
    printf("Pai leu: %s", (char *)ptr);

    7. Por fim, o pai deve desvincular a memória compartilhada, removendo sua exis-
    tência com shm_unlink
    shm_unlink(name);

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
    const int SIZE = 4096;
    const char *name = "/prod_cons";

    int shm_fd;
    void *ptr; 
    const char *message_0 = "Hello";
    const char *message_1 = " World!";

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (ptr == MAP_FAILED) {
        printf("Falha no mapeamento da memória\n");
        return -1;
    }

    pid_t pid = fork();

    if(pid == 0) {
        char *cptr = (char *)ptr;        

        sprintf(cptr, "%s", message_0);
        cptr += strlen(message_0);

        sprintf(cptr, "%s", message_1);
        cptr += strlen(message_1);

        sprintf(cptr, "\n");
        cptr += 1;

        exit(0);
    } else {
        wait(NULL);
        printf("Pai leu: %s", (char *)ptr);
        shm_unlink(name);
    }
    return 0;
}