#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
int global_var;
pthread_mutex_t a_mutex;
void *do_thread1 (void *data);
void *do_thread2(void *data);
int main() {
    int res;
    pthread_t p_thread1;
    pthread_t p_thread2;
    res = pthread_mutex_init(&a_mutex, NULL);
    if(res != 0) {
        perror("Loi tao mutex!");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&p_thread1, NULL, do_thread1, NULL);
    if(res != 0) {
        perror("Loi tao thread!");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&p_thread2, NULL, do_thread2, NULL);
    if(res != 0) {
        perror("Loi tao thread!");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < 20; i++) {
        printf("Thread chinh dang cho %d giay... \n", i);
        sleep(1);
    }
    return 0;
}
void *do_thread1(void *data) {
  pthread_mutex_lock(&a_mutex);
  for(int i = 1; i <= 5; i++) {
    printf("Luong 1 dem: %d voi bien toan cuc la %d \n", i, global_var++);
    sleep(1);
  }
  pthread_mutex_unlock(&a_mutex);
  printf("Thread 1 hoan tat!\n");
}

void *do_thread2(void *data) {
pthread_mutex_lock(&a_mutex);
  for(int i = 1; i <= 5; i++) {
    printf("Luong 2 dem: %d voi bien toan cuc la %d \n", i, global_var++);
    sleep(2);
  }
  pthread_mutex_unlock(&a_mutex);
  printf("Thread 2 hoan tat!\n");
}
