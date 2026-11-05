
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

long copy_file(const char *src, const char *dst, size_t bufsize)
{
    char buf[8192];

    if (bufsize == 0 || bufsize > sizeof(buf))
        return -1;

    int in = open(src, O_RDONLY);
    if (in < 0) {
        perror("open source");
        return -1;
    }

    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) {
        perror("open destination");
        close(in);
        return -1;
    }

    long calls = 0;
    ssize_t n;

    while (1) {
        do {
            n = read(in, buf, bufsize);
            calls++;
        } while (n < 0 && errno == EINTR);

        if (n < 0) {
            perror("read");
            calls = -1;
            break;
        }

        if (n == 0)
            break;

        ssize_t written = 0;

        while (written < n) {
            ssize_t w = write(out, buf + written,
                              (size_t)(n - written));

            if (w < 0) {
                if (errno == EINTR)
                    continue;

                perror("write");
                calls = -1;
                break;
            }

            written += w;
        }

        if (calls == -1)
            break;
    }

    close(in);
    close(out);

    return calls;
}

int main(void)
{
    FILE *fp = fopen("testfile.txt", "w");

    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    for (int i = 0; i < 10000; i++)
        fputc('A', fp);

    fclose(fp);

    size_t sizes[] = {1, 512, 4096};

    for (int i = 0; i < 3; i++) {
        char destination[40];

        snprintf(destination, sizeof(destination),
                 "copy_%zu.txt", sizes[i]);

        long calls = copy_file("testfile.txt",
                               destination, sizes[i]);

        if (calls < 0)
            return 1;

        printf("buffer %4zu bytes: %5ld read() calls\n",
               sizes[i], calls);
    }

    return 0;
}
