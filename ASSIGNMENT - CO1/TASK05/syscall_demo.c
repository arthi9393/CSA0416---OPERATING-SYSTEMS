#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char buffer[100];
    int fd = open("input.txt", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[n] = '\0';

    printf("Data read from file: %s\n", buffer);
    printf("Number of bytes read: %zd\n", n);

    close(fd);
    return 0;
}
