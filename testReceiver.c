#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/shmem_device"
#define PAGE_SIZE 4096

int main() {
    int fd;
    char *mapped_mem;

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    mapped_mem = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        perror("Failed to map the device to memory");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Application B read: %s\n", mapped_mem);

    munmap(mapped_mem, PAGE_SIZE);
    close(fd);

    return EXIT_SUCCESS;
}
