#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *dorme(void *arg) {
  long id = (long)arg;
  sleep(60);
  printf("Thread %ld dormindo....\n", id);
  pthread_exit(NULL);
}

int main() {
  pthread_t t1, t2, t3;
  printf("Criando 3 threads. Meu PID é: %d\n", getpid());


  pthread_create(&t1, NULL, dorme, (void *)1);
  pthread_create(&t1, NULL, dorme, (void *)2);
  pthread_create(&t1, NULL, dorme, (void *)3);
  

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  
  return 0;
}
