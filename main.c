#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "funcs.h"
#include "monitor.h"

pthread_t t_fim, t[4];
int id[] = {0, 1, 2, 3};

int main(void) {
    int i;

    pthread_create(&t_fim, NULL, (void *) fun_fim, NULL);

    for(i=0; i<4; i++) {
        pthread_create(&t[i], NULL, (void *) fun_random, &id[i]);
    }

    pthread_join(t_fim, NULL);
    for(i=0; i<4; i++) {
        pthread_join(t[i], NULL);
    }

    return 0;
}

void fun_fim(void) {
    printf("Esperando as outras threads.\n");
    espera_todos();
    printf("Sou a ultima thread.\n");
}

void fun_random(int *id) {
    printf("Sou a thread: %d\n", *id);
    sleep(3);
    termina();
    printf("Fim da thread: %d\n", *id);
}
