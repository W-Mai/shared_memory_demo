//
// Created by W-Mai on 2024/4/29.
//

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    printf("Hello from the shared client!\n");

    int shm_fd = shm_open("./my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    void *shm_ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("The value in the shared memory is: %s\n", (char *) shm_ptr);

    // Modify the value in the shared memory
    strcpy((char *) shm_ptr, "Hello from the shared server!");

    // Unmap the shared memory
    if (munmap(shm_ptr, 1024) == -1) {
        perror("munmap");
        return 1;
    }

    // Close the shared memory file descriptor
    if (close(shm_fd) == -1) {
        perror("close");
        return 1;
    }

    // Unlink the shared memory file
    shm_unlink("./my_shared_memory");

    return 0;
}
