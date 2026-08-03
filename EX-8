#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
 
#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10
 
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
 
sem_t empty;   /* counts empty slots  */
sem_t full;    /* counts filled slots */
pthread_mutex_t mutex; /* protects buffer access */
 
void *producer(void *arg)
{
    int item;
    for (item = 1; item <= ITEMS_TO_PRODUCE; item++) {
        sem_wait(&empty);              /* wait for an empty slot   */
        pthread_mutex_lock(&mutex);    /* enter critical section   */
 
        buffer[in] = item;
        printf("Producer produced item %d at slot %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);  /* leave critical section   */
        sem_post(&full);               /* signal a new filled slot */
 
        usleep(100000); /* simulate production time */
    }
    return NULL;
}
 
void *consumer(void *arg)
{
    int item;
    for (int count = 1; count <= ITEMS_TO_PRODUCE; count++) {
        sem_wait(&full);               /* wait for a filled slot   */
        pthread_mutex_lock(&mutex);    /* enter critical section   */
 
        item = buffer[out];
        printf("\tConsumer consumed item %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);  /* leave critical section   */
        sem_post(&empty);              /* signal a new empty slot  */
 
        usleep(150000); /* simulate consumption time */
    }
    return NULL;
}
 
int main()
{
    pthread_t prod_thread, cons_thread;
 
    sem_init(&empty, 0, BUFFER_SIZE); /* initially all slots empty */
    sem_init(&full, 0, 0);            /* initially no slots filled */
    pthread_mutex_init(&mutex, NULL);
 
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
 
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
 
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
 
    printf("\nAll items produced and consumed successfully.\n");
    return 0;
}
 
/* Compile with: gcc producer_consumer.c -o producer_consumer -lpthread */
