#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main () {
    const int  SIZE = 4096;
    const char *name = "/prod_cons";

    int shm_fd;
    void *ptr;

    shm_fd = shm_open(name, O_RDONLY, 0666);

    if (shm_fd == -1) {
        fprintf(stderr, "Não existe memória compartilhada com nome de %s\n", name);
        return 1;
    }
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("Consumidor leu: %s", (char *) ptr);

    shm_unlink(name);

    return 0;
    
}
