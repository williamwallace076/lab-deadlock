#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t file1_mutex, file2_mutex;

void *processA(void *arg) {
    // Adquire os mutexes na mesma ordem para prevenir deadlock
    pthread_mutex_lock(&file1_mutex);
    printf("Processo A abriu o arquivo 1\n"); 
    sleep(1); // Simula algum processamento com o arquivo 1

    pthread_mutex_lock(&file2_mutex);
    printf("Processo A abriu o arquivo 2\n");
    printf("Processo A consumindo arquivos 1 e 2\n");

    // Libera os mutexes na ordem inversa
    pthread_mutex_unlock(&file2_mutex);
    pthread_mutex_unlock(&file1_mutex);

    return NULL;
}

void *processB(void *arg) {
    // Adquire os mutexes na mesma ordem para prevenir deadlock
    pthread_mutex_lock(&file1_mutex);
    printf("Processo B abriu o arquivo 1\n");
    sleep(1); // Simula algum processamento com o arquivo 1

    pthread_mutex_lock(&file2_mutex);
    printf("Processo B abriu o arquivo 2\n");
    printf("Processo B consumindo arquivos 1 e 2\n");

    // Libera os mutexes na ordem inversa
    pthread_mutex_unlock(&file2_mutex);
    pthread_mutex_unlock(&file1_mutex);

    return NULL;
}

int main() {
    pthread_t t1, t2; // variáveis que armazenam os IDs das threads
    pthread_mutex_init(&file1_mutex, NULL); // inicializa o mutex do arquivo 1
    pthread_mutex_init(&file2_mutex, NULL); // inicializa o mutex do arquivo 2

    pthread_create(&t1, NULL, processA, NULL); // cria a thread para o processo A
    pthread_create(&t2, NULL, processB, NULL); // cria a thread para o processo B

    pthread_join(t1, NULL); // aguarda a conclusão do processo A
    pthread_join(t2, NULL); // aguarda a conclusão do processo B

    pthread_mutex_destroy(&file1_mutex); // destrói o mutex do arquivo 1
    pthread_mutex_destroy(&file2_mutex); // destrói o mutex do arquivo 2

    return 0;
}
