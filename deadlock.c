#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t file1_mutex, file2_mutex;

void *processA(void *arg) {
    pthread_mutex_lock(&file1_mutex); // bloqueia o arquivo 1
    printf("Processo A abriu o arquivo 1\n"); 
    sleep(2); // Simula algum processamento com o arquivo 1

    pthread_mutex_lock(&file2_mutex); // tenta bloquear o arquivo 2
    printf("Processo A abriu o arquivo 2\n");

    // simula o uso dos dos arquivos
    printf("Processo A consumindo arquivos 1 e 2\n");

    // Libera os arquivos
    pthread_mutex_unlock(&file2_mutex);
    pthread_mutex_unlock(&file1_mutex);
  
}

void *processB(void *arg) {
  
    pthread_mutex_lock(&file2_mutex);
    printf("Processo B abriu o arquivo 2\n");
    sleep(2); // Simula algum processamento com o arquivo 1
  
    pthread_mutex_lock(&file1_mutex);
    printf("Processo B abriu o arquivo 1\n"); 

    // simula o uso dos dos arquivos
    printf("Processo A consumindo arquivos 1 e 2\n");

    // Release locks
    pthread_mutex_unlock(&file1_mutex);
    pthread_mutex_unlock(&file2_mutex);
}

int main() {
    pthread_t t1, t2; // variavel que armazena os endereços do Proc. 1 e 2. 
    pthread_mutex_init(&file1_mutex, NULL);
    pthread_mutex_init(&file2_mutex, NULL);

    pthread_create(&t1, NULL, processA, NULL);
    pthread_create(&t2, NULL, processB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&file1_mutex);
    pthread_mutex_destroy(&file2_mutex);

  return 0;

}

