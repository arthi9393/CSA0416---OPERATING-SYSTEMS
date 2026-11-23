/* Q24: Demonstrate UNIX system calls for file management (CO1)
   open, write, read, lseek, close, link, unlink, dup, rename */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    char buf[100];
    const char *msg = "Hello, UNIX file system calls!\n";
    ssize_t n;

    int fd = open("demo.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(1); }
    printf("open()   : fd = %d\n", fd);

    n = write(fd, msg, strlen(msg));
    printf("write()  : %zd bytes written\n", n);

    lseek(fd, 0, SEEK_SET);
    n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("read()   : %zd bytes read -> %s", n, buf);

    int fd2 = dup(fd);
    printf("dup()    : duplicate descriptor = %d\n", fd2);
    close(fd2);

    close(fd);
    printf("close()  : file closed\n");

    if (link("demo.txt", "demo_link.txt") == 0) printf("link()   : hard link demo_link.txt created\n");
    if (rename("demo_link.txt", "demo_renamed.txt") == 0) printf("rename() : renamed to demo_renamed.txt\n");
    if (unlink("demo_renamed.txt") == 0) printf("unlink() : demo_renamed.txt removed\n");
    if (unlink("demo.txt") == 0) printf("unlink() : demo.txt removed\n");
    return 0;
}
