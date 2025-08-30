/*
 * Producer–Consumer problem using POSIX threads, mutex, and condition variables.
 *
 * - One producer thread generates items and places them into a bounded buffer.
 * - One consumer thread removes items from the buffer.
 * - A mutex ensures mutual exclusion when accessing the shared buffer.
 * - Two condition variables coordinate access:
 *      - not_full:  producer waits if buffer is full.
 *      - not_empty: consumer waits if buffer is empty.
 * - This avoids busy-waiting (no sleep-based polling).
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;   // number of items in buffer

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int item = 0;
    while (1) {
        sleep(1); // simulate production delay
        item++;

        pthread_mutex_lock(&lock);
        while (count == BUFFER_SIZE) {
            // buffer full → wait until consumer signals
            pthread_cond_wait(&not_full, &lock);
        }

        // add item to buffer
        buffer[count++] = item;
        printf("Producer: produced item %d (buffer count = %d)\n", item, count);

        // signal consumer that buffer is not empty
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (count == 0) {
            // buffer empty → wait until producer signals
            pthread_cond_wait(&not_empty, &lock);
        }

        // consume item
        int item = buffer[--count];
        printf("Consumer: consumed item %d (buffer count = %d)\n", item, count);

        // signal producer that buffer has space
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);

        sleep(2); // simulate consumption delay
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
