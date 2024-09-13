#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t file1_mutex, file2_mutex;

void *processA(void *arg) {
    pthread_mutex_lock(&file1_mutex); // bloqueia o arquivo 1
    printf("Processo A abriu o arquivo 1\n"); 
    sleep(2); // Simula algum processamento com o arquivo 1

    // Tenta adquirir o mutex do arquivo 1
    if (pthread_mutex_trylock(&file2_mutex) != 0) {  // Verifica se o arquivo 1 está bloqueado
        printf("Processo A: Deadlock detectado durante a tentativa de acesso do arquivo 2\n");
    } else {
        printf("Processo A: Sem detecção de Deadlock durante a abaertura do arquivo \n");
        printf("Processo A abriu o arquivo 2\n");

        // simula o uso dos dos arquivos
        printf("Processo A consumindo arquivos 1 e 2\n");
        pthread_mutex_unlock(&file2_mutex); // libera o arquivo 2
    }
    
    pthread_mutex_unlock(&file1_mutex);    // Libera o arquivo 1
  
}

void *processB(void *arg) {
    sleep(1); // atrasando o processo b
    pthread_mutex_lock(&file2_mutex);
    printf("Processo B abriu o arquivo 2\n");
    sleep(2); // Simula algum processamento com o arquivo 1


     // Tenta adquirir o mutex do arquivo 1
    if (pthread_mutex_trylock(&file1_mutex) != 0) {  // Verifica se o arquivo 1 está bloqueado
        printf("Processo B: Deadlock detectado durante a tentativa de acesso do arquivo 1\n");
    } else {
        printf("Processo B: Sem detecção de Deadlock durante a abaertura do arquivo \n");
        printf("Processo B abriu o arquivo 1\n"); 

        // simula o uso dos dos arquivos
        printf("Processo A consumindo arquivos 1 e 2\n");
        
        pthread_mutex_unlock(&file1_mutex); // libera o arquivo 1
    }
  
    pthread_mutex_unlock(&file2_mutex); // libera o arquivo 2
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

