#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main() {
    const char msg[] = "Essa mensagem ocorreu por meio de uma syscall!\n";

    long err = syscall(600, 1, msg, sizeof(msg) - 1);
    if (err == -1) {
        fprintf(stderr, "Erro ao realizar a chamada de sistema!\n");
        return 1;
    }
    return 0;
}