#include <pthread.h>

pthread_mutex_t ex_mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t todas_threads_terminaram = PTHREAD_COND_INITIALIZER;

int num_threads = 0;

void termina(void) {
    pthread_mutex_lock(&ex_mut);

    if (++num_threads == 4 ) {
        pthread_cond_signal(&todas_threads_terminaram);
    }

    pthread_mutex_unlock(&ex_mut);
}

void espera_todos(void) {
    pthread_mutex_lock(&ex_mut);

    while(num_threads < 4) {
        pthread_cond_wait(&todas_threads_terminaram, &ex_mut);
    }

    pthread_mutex_unlock(&ex_mut);
}
