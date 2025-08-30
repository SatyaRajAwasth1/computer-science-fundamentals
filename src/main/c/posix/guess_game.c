/*
 * Simple Number Guessing Game using POSIX Threads
 *
 * Description:
 * This program generates a random number between 1 and 10,
 * then creates a separate thread to prompt the user to guess the number.
 * The thread compares the user input to the generated number and prints
 * whether the guess was correct or not.
 *
 * Demonstrates:
 * - Basic usage of POSIX threads (pthreads)
 * - Passing arguments to a thread function
 * - Handling user input
 *
 * Compilation:
 * gcc -o guess_game guess_game.c -pthread
 *
 * Or Use this all in one line (compile, run and remove the object file)
 * gcc -o guess_game guess_game.c -pthread && ./guess_game && rm guess_game
 *
 * Usage:
 * ./guess_game
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* run(void *number) {
    int* num = (int*) number;
    printf("Guess the number between 1 to 10: ");

    int user_input;
    if (scanf("%d", &user_input) != 1) {
        printf("Invalid input.\n");
        return NULL;
    }

    if (*num == user_input) {
        printf("Congratulations! You win it.\n");
    } else {
        printf("Sorry, bad luck! Try next time. The number was '%d'.\n", *num);
    }

    return NULL;
}

int main() {
    pthread_t thread1;

    // Seed the random number generator
    srand(time(NULL));
    int guess = (rand() % 10) + 1;

    // Create thread and pass the random number
    pthread_create(&thread1, NULL, run, &guess);

    // Wait for the thread to complete
    pthread_join(thread1, NULL);

    return 0;
}
