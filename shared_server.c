#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

int main(void) {

    printf("Hello from the shared server!\n");

    // Get a handle to the shared memory segment
    int shm_id = shmget(1234, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory segment to this process
    void *shm_ptr = shmat(shm_id, NULL, 0);

    // Write to the shared memory segment
    char *msg = "Hello from the server!";
    memcpy(shm_ptr, msg, strlen(msg) + 1);

    // Detach the shared memory segment from this process
    shmdt(shm_ptr);

    return 0;
}
