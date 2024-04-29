//
// Created by W-Mai on 2024/4/29.
//

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main() {
    printf("Hello from the shared client!\n");


    // Get a handle to the shared memory segment
    int shm_id = shmget(1234, 1024, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        return 1;
    }


    // Attach the shared memory segment to this process
    void *shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *) -1) {
        perror("shmat");
        return 1;
    }

    // Print the contents of the shared memory segment
    printf("The contents of the shared memory segment are: %s\n", (char *) shm_ptr);

    // Detach the shared memory segment from this process
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        return 1;

    }


    // Destroy the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return 1;
    }

    return 0;
}
