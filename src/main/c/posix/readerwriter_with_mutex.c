/*
* A program showing a single reader and a single writer communicating via shared memory - synchornized using mutex
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define SET 1
#define NOTSET 0

int info_in_buffer = NOTSET;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Optionally pthread_mutex_init(&lock, NULL); can also be used

void* reader(void* arg) {
        while (1) {
    pthread_mutex_lock(&lock);
    if (info_in_buffer == SET) {
        printf("\n Reader -> Reading data from buffer .... "); 
        // read_buffered_data(&some_var) Reading from buffer logic goes here
        sleep(2); // Sleep for 2 seconds for simulation
        
        info_in_buffer = NOTSET; // Empty/clear buffer
    } 

    pthread_mutex_unlock(&lock);
    // Give writer 2 seconds to write before polling
    sleep(2);
    }
}

void* writer(void* arg) {
         while (1) {
    pthread_mutex_lock(&lock);
    if (info_in_buffer == NOTSET) {
        printf("\n Writer -> Writing data to buffer .... "); 
        // write_data_to_buffer(&buffer, some_data) Logic writing data to buffer goes here
        sleep(2); // Sleep for 2 seconds for simulation; Assuming it takes 2 seconds to write data
        
        info_in_buffer = SET; // Set that buffer contains data
    } 

    pthread_mutex_unlock(&lock);
    // Give Reader 2 seconds to read before atempting to write data
    sleep(2);
    }
}

int main() {
    pthread_t reader_thread, writer_thread;

     pthread_create(&reader_thread, NULL, reader, NULL);
    pthread_create(&writer_thread, NULL, writer, NULL);

    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);

    return 0;
}