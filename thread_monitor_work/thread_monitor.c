#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct ThreadData {
    int id;
    int buffersProcessed;
} ThreadData;

static int buffer[3];
static int bufferRead[3] = { 1, 1, 1 };

static sem_t items;
static pthread_mutex_t mutex;
static sem_t spaces; 

enum {
    N_PRODUCERS = 4,
    N_CONSUMERS = 4,
    MAX_BUF_LENGTH = 3,
    NLOOPS = 1000
};

static int producerIds[5] = { 0,1,2,3,4 };

static ThreadData consumerThreadDatas[N_CONSUMERS];
static ThreadData producerThreadDatas[N_PRODUCERS];

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

static void itemsWait() {
  if(sem_wait(&items) == -1){
      errExit("producerWait");
  }
}

static void spacesWait() {
  if(sem_wait(&spaces) == -1){
      errExit("consumerWait");
  }
}

static void itemsPost() {
  if(sem_post(&items) == -1){
      errExit("producerPost");
  }
}

static void spacesPost() {
  if(sem_post(&spaces) == -1){
      errExit("consumerPost");
  }
}

static int getBufferRead(int value) {
    for (size_t i = 0; i < MAX_BUF_LENGTH; i++) {
        if(bufferRead[i] == value) {
            return i;
        }
    }
    return -1;
}

void incProducerBufferCounter(int id) {
    for (size_t i = 0; i < N_PRODUCERS; i++) {
        if(id == producerThreadDatas[i].id) {
            producerThreadDatas[i].buffersProcessed++;
        }
    }
}

void incConsumerBufferCounter(int id) {
    for (size_t i = 0; i < N_CONSUMERS; i++) {
        if(id == consumerThreadDatas[i].id) {
            consumerThreadDatas[i].buffersProcessed++;
        }
    }
}

static void *producersFunc(void *arg)
{
    int prodNr = *((int *) arg); 
    char current;
    int bufferPos = 0;
    for (size_t i = 0; i < NLOOPS; i++) {

        spacesWait();
        pthread_mutex_lock(&mutex);
        bufferPos = getBufferRead(1);
        if(bufferPos == -1) {
            errExit("BufferPos -1 in producer");
        }
        bufferRead[bufferPos] = 0;

        buffer[bufferPos] = prodNr;
        incProducerBufferCounter(prodNr-1);
        pthread_mutex_unlock(&mutex);
        itemsPost();
    }

    return NULL;
}

static void *consumersFunc(void *arg)
{
    int consNr = *((int *) arg); 
    char buffer_copy;
    int bufferPos = 0;
    for (size_t i = 0; i < NLOOPS; i++) {
        itemsWait();
        pthread_mutex_lock(&mutex);
        bufferPos = getBufferRead(0);
        if(bufferPos == -1) {
            errExit("BufferPos -1 in consumer");
        }
        bufferRead[bufferPos] = 1;

        buffer_copy = buffer[bufferPos];
        incConsumerBufferCounter(consNr-1);
        pthread_mutex_unlock(&mutex);
        spacesPost();
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t producers[N_PRODUCERS];
    pthread_t consumers[N_CONSUMERS];
    int s;
    long nloops = 10000;

    if(pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }

    if (sem_init(&items, 0, 0) == -1)
        errExit("sem_init");
    if (sem_init(&spaces, 0, MAX_BUF_LENGTH) == -1)
        errExit("sem_init");
    
    for (int i = 1; i <= N_PRODUCERS; ++i) {
        producerThreadDatas[i].buffersProcessed = 0; 
        producerThreadDatas[i].id = i;
        s = pthread_create(&producers[i], NULL, producersFunc, &producerIds[i]);
        if (s != 0)
            errExit("pthread_create");
    }
    for (int i = 1; i <= N_CONSUMERS; ++i) {
        consumerThreadDatas[i].buffersProcessed = 0; 
        consumerThreadDatas[i].id = i;
        s = pthread_create(&consumers[i], NULL, consumersFunc, &producerIds[i]);
        if (s != 0)
            errExit("pthread_create");
    }

    for (int i = 1; i <= N_CONSUMERS; ++i) {
        s = pthread_join(consumers[i], NULL);
        if (s != 0)
            errExit("pthread_join");
    }
    for (int i = 1; i <= N_PRODUCERS; ++i) {
        s = pthread_join(producers[i], NULL);
        if (s != 0)
            errExit("pthread_join");
    }
    for (int i = 1; i <= N_CONSUMERS; ++i) {
        printf("consumer %i processed %i buffers\n", consumerThreadDatas[i].id, consumerThreadDatas[i].buffersProcessed); 
    }
    for (int i = 1; i <= N_PRODUCERS; ++i) {
        printf("producer %i processed %i buffers\n", producerThreadDatas[i].id, producerThreadDatas[i].buffersProcessed); 
    }

    exit(EXIT_SUCCESS);
}
