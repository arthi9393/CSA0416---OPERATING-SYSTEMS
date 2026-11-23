/* Q25: I/O system calls of UNIX - fcntl, lseek, stat, opendir, readdir (CO5) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    char buf[64];
    int fd = open("io_demo.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }
    write(fd, "0123456789ABCDEFGHIJ", 20);

    /* fcntl */
    int flags = fcntl(fd, F_GETFL);
    printf("fcntl(F_GETFL): flags = %d, access mode = %s\n", flags,
           (flags & O_ACCMODE) == O_RDWR ? "O_RDWR" : "other");
    fcntl(fd, F_SETFL, flags | O_APPEND);
    printf("fcntl(F_SETFL): O_APPEND %s\n", (fcntl(fd, F_GETFL) & O_APPEND) ? "set" : "not set");
    int nfd = fcntl(fd, F_DUPFD, 10);
    printf("fcntl(F_DUPFD): duplicate descriptor = %d\n", nfd);
    close(nfd);

    /* lseek */
    off_t pos = lseek(fd, 5, SEEK_SET);
    ssize_t n = read(fd, buf, 5); buf[n] = '\0';
    printf("lseek(5, SEEK_SET) -> %ld, read 5 bytes: %s\n", (long)pos, buf);
    printf("lseek(0, SEEK_END) -> file size = %ld\n", (long)lseek(fd, 0, SEEK_END));
    close(fd);

    /* stat */
    struct stat st;
    if (stat("io_demo.txt", &st) == 0) {
        printf("\nstat(io_demo.txt):\n");
        printf("  inode      : %lu\n", (unsigned long)st.st_ino);
        printf("  size       : %ld bytes\n", (long)st.st_size);
        printf("  links      : %lu\n", (unsigned long)st.st_nlink);
        printf("  permissions: %o\n", st.st_mode & 0777);
        printf("  uid / gid  : %d / %d\n", st.st_uid, st.st_gid);
        printf("  modified   : %s", ctime(&st.st_mtime));
    }

    /* opendir / readdir */
    DIR *d = opendir(".");
    if (!d) { perror("opendir"); return 1; }
    struct dirent *e;
    printf("\nopendir(\".\") / readdir():\n");
    while ((e = readdir(d)) != NULL)
        printf("  %-25s inode %lu\n", e->d_name, (unsigned long)e->d_ino);
    closedir(d);

    unlink("io_demo.txt");
    return 0;
}
