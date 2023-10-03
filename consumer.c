#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int product_val = 2;
sem_t semaphore;
void *do_thread (void *data);
int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    res = sem_init(&semaphore, 0, 2);
    if(res != 0) {
        perror("Loi thiet lap semaphore\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, NULL, do_thread, NULL);
    if(res != 0) {
        perror("Loi tao thread\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 5; i++) {
        product_val++;
        printf("Producer product_val = %d \n\n", product_val);
        sem_post(&semaphore);
        sleep(2);
    }
    printf("Tat ca hoan tat!\n");
    exit(EXIT_SUCCESS);
    return 0;
}
void *do_thread(void *data) {
    printf("Ham consumer thread dang chay...\n");
    while(1) {
        sem_wait(&semaphore);
        product_val--;
        printf("Consumer product_val = %d \n", product_val);
        sleep(1);
    }
    pthread_exit(NULL);
}
