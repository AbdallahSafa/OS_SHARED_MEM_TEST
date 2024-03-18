#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/shmem_device", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Use mmap to map the device into memory
    void *mapped_mem = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    // Now you can use the shared memory region
    // For example, write something to it
    const char *message = "Hello, Kernel!";
    strcpy((char *)mapped_mem, message);

    // Remember to unmap the memory before exiting
    munmap(mapped_mem, getpagesize());
    close(fd);
    return EXIT_SUCCESS;
}
