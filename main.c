#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int saldo = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *deposito(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        saldo += 20;
        printf("Depósito Efetuado! Saldo atual: %d\n", saldo);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *saque(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        if (saldo >= 20) {
            saldo -= 20;
            printf("Saque Efetuado! Saldo atual: %d\n", saldo);
        }
        else {
            saldo = 0;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[8];
    int i;

    // cria threads de deposito e saque
    for (i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, deposito, NULL);
        pthread_create(&threads[i+4], NULL, saque, NULL);
    }

    // espera pelo término de todas as threads
    for (i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Saldo final: %d\n", saldo);

    return 0;
}
