#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
void *do_thread(void *data);
int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    res = pthread_create(&a_thread, NULL, do_thread, NULL);
    if (res != 0) {
        perror("Loi tao thread!\n");
        exit(EXIT_FAILURE);
    }
    sleep(3);
    printf("Thu lai viec huy thread...\n");
    res = pthread_cancel(a_thread);
    if (res != 0) {
        perror("Loi huy thread!\n");
        exit(EXIT_FAILURE);
    }

    printf("Dang cho thread hoan tat...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Loi cho thread!\n");
        exit(EXIT_FAILURE);
    }

    printf("Tat ca hoan tat!\n");
    exit(EXIT_SUCCESS);
}

void *do_thread(void *data) {
    int res;
    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (res != 0) {
        perror("Dat trang thai huy thread that bai!");
        exit(EXIT_FAILURE);
    }
    res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    if (res != 0) {
        perror("Loai huy thread that bai!");
        exit(EXIT_FAILURE);
    }
    printf("Ham thread dang chay...\n");
    for (int i = 0; i < 10; i++) {
        printf("Thread van dang chay (%d)...\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
}
