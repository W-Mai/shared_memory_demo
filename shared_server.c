#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {

    printf("Hello from the shared server!\n");

    // Create a shared memory segment using
    int shm_fd = shm_open("./my_shared_memory", O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Resize the shared memory segment to 1024 bytes
    if (ftruncate(shm_fd, 1024) == -1) {
        perror("ftruncate");
        return 1;
    }

    // Map the shared memory segment into this process's address space
    void *shm_ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Write to the shared memory segment
    char *msg = "Hello from the server!";
    memcpy(shm_ptr, msg, strlen(msg) + 1);

    // Unmap the shared memory segment
    if (munmap(shm_ptr, 1024) == -1) {
        perror("munmap");
        return 1;
    }

    // Close the shared memory segment
    if (close(shm_fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
