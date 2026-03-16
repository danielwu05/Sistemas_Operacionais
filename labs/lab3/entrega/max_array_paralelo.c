#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct  {
  int *vetor;

  long lim_inf;
  long lim_sup;

  int max_loc;
}ThreadArgs;

double calcula_tempo (struct timespec start, struct timespec end) {
  return (end.tv_sec - start.tv_sec) * 1000 + (double) (end.tv_nsec - start.tv_nsec) / 1000000;
}

void *encontra_maximo_local (void *arg) {
  ThreadArgs *args_local = (ThreadArgs*) arg;
  int max = args_local->vetor[args_local->lim_inf - 1];
  for (int i = args_local->lim_inf; i <= args_local->lim_sup; ++i) {
    if (max < args_local->vetor[i]) {
      max = args_local->vetor[i];
    }
  }

  args_local->max_loc = max;
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  

  if (argc < 3) {
    fprintf(stderr, "Uso: %s <tamanho> <num_threads>\n", argv[0]);
    return 1;
  }  
  long tamanho = atol(argv[1]);
  int num_threads = atoi(argv[2]);
  
  int *vetor = (int *)malloc(tamanho * sizeof(int));

  pthread_t threads[num_threads];
  ThreadArgs argumento[num_threads];

  if (num_threads <= 0) {
    fprintf(stderr, "Numero de threads deve ser maior que 0\n");
    return 1;
  }
  
  srand(time(NULL));
  for (long i = 0; i < tamanho; ++i) {
    vetor[i] = rand() % 1000000;
  }
  vetor[tamanho / 2] = 2000000;
  
  const long constante = tamanho/num_threads;

  struct timespec start, end;

  clock_gettime(CLOCK_MONOTONIC, &start);

  for (int j = 0; j < num_threads; ++j) {
    argumento[j].vetor = vetor;
    argumento[j].lim_inf = j*constante;
    argumento[j].lim_sup = (j == num_threads - 1) ? (tamanho - 1) : ((j + 1) * constante - 1);    
    pthread_create(&threads[j], NULL, encontra_maximo_local, (void *)&argumento[j]);
  }
  long maximo_global = -1;
  for (int j = 0; j < num_threads; ++j) { 
    pthread_join(threads[j], NULL);
    if (maximo_global < argumento[j].max_loc) maximo_global = argumento[j].max_loc;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  double tempo_gasto = calcula_tempo(start, end);

  printf("Maior elemento (Paralelo): %d\n", maximo_global);
  printf("Tempo Paralelo: %lf ms\n", tempo_gasto);


  return 0;
}
