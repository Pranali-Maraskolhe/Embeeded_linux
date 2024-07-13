#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define MAX_THREADS 5

void* thread_function(void* arg) {
    int core_id = *(int*)arg;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t thread = pthread_self();
    int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_setaffinity_np");
    }

    // Confirm CPU affinity setting
    CPU_ZERO(&cpuset);
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_getaffinity_np");
    }

    if (CPU_ISSET(core_id, &cpuset)) {
        printf("Thread %d is running on CPU %d\n", core_id, core_id);
    } else {
        printf("Thread %d is not running on the expected CPU %d\n", core_id, core_id);
    }

    // Simulate work
    for (int i = 0; i < 100000000; i++);  // Simulate some work with a busy loop

    return NULL;
}

int main() {
    pthread_t threads[MAX_THREADS];
    int core_ids[MAX_THREADS];
    int ret, n;

    printf("The process id: %d\n", getpid());
    printf("Enter number of threads (max %d): ", MAX_THREADS);
    scanf("%d", &n);

    if (n > MAX_THREADS) {
        printf("Number of threads exceeds the limit of %d\n", MAX_THREADS);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        core_ids[i] = i % sysconf(_SC_NPROCESSORS_ONLN);  // Assign core id
        printf("Creating thread %d on core %d\n", i + 1, core_ids[i]);
        ret = pthread_create(&threads[i], NULL, thread_function, &core_ids[i]);

        if (ret == 0) {
            printf("Thread %d created successfully\n", i + 1);
        } else {
            printf("Problem in creating thread %d\n", i + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Joining thread %d\n", i + 1);
        ret = pthread_join(threads[i], NULL);
        if (ret) {
            printf("Unable to join thread %d: %d\n", i + 1, ret);
        } else {
            printf("Thread %d has terminated\n", i + 1);
        }

        printf("Detaching thread %d\n", i + 1);
        ret = pthread_detach(threads[i]);
        if (ret) {
            printf("Error detaching thread %d: %d\n", i + 1, ret);
        }
    }

    return 0;
}

