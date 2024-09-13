#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t file1_mutex, file2_mutex;

#define TIME_LIMIT_SEC 2 // Tempo limite para detecção de deadlock em segundos

void *processA(void *arg) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += TIME_LIMIT_SEC; // Define o tempo limite para o mutex

    pthread_mutex_lock(&file1_mutex); // bloqueia o arquivo 1
    printf("Processo A abriu o arquivo 1\n");
    sleep(1); // Simula algum processamento com o arquivo 1

    // Tenta adquirir o mutex do arquivo 2
    if (pthread_mutex_timedlock(&file2_mutex, &ts) != 0) {  // Verifica se o arquivo 2 está bloqueado
        if (errno == ETIMEDOUT) {
            printf("Processo A: Deadlock detectado durante a tentativa de acesso ao arquivo 2\n");
            // Libera o recurso já adquirido
            pthread_mutex_unlock(&file1_mutex);
            printf("Processo A: Recursos liberados\n");
        } else {
            perror("pthread_mutex_timedlock");
        }
    } else {
        printf("Processo A abriu o arquivo 2\n");
        printf("Processo A consumindo arquivos 1 e 2\n");
        pthread_mutex_unlock(&file2_mutex); // libera o arquivo 2
    }
    
    pthread_mutex_unlock(&file1_mutex); // Libera o arquivo 1
    return NULL;
}

void *processB(void *arg) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += TIME_LIMIT_SEC; // Define o tempo limite para o mutex

    sleep(1);
    pthread_mutex_lock(&file2_mutex); // bloqueia o arquivo 2
    printf("Processo B abriu o arquivo 2\n");
    sleep(1); // Simula algum processamento com o arquivo 2

    // Tenta adquirir o mutex do arquivo 1
    if (pthread_mutex_timedlock(&file1_mutex, &ts) != 0) {  // Verifica se o arquivo 1 está bloqueado
        if (errno == ETIMEDOUT) {
            printf("Processo B: Deadlock detectado durante a tentativa de acesso ao arquivo 1\n");
            // Libera o recurso já adquirido
            pthread_mutex_unlock(&file2_mutex);
            printf("Processo B: Recursos liberados\n");
        } else {
            perror("pthread_mutex_timedlock");
        }
    } else {
        printf("Processo B abriu o arquivo 1\n");
        printf("Processo B consumindo arquivos 1 e 2\n");
        pthread_mutex_unlock(&file1_mutex); // libera o arquivo 1
    }
    
    pthread_mutex_unlock(&file2_mutex); // libera o arquivo 2
    return NULL;
}

int main() {
    pthread_t t1, t2;

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
