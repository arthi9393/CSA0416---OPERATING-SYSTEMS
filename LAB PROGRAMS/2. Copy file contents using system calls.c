
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char s[100], d[100], b[1024];
    int a, c, n;
    scanf("%99s%99s", s, d);
    a = open(s, O_RDONLY);
    if (a < 0) { perror("Source"); return 1; }
    c = open(d, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (c < 0) { perror("Destination"); close(a); return 1; }
    while ((n = read(a, b, sizeof(b))) > 0)
        if (write(c, b, n) != n) { perror("Write"); break; }
    close(a); close(c);
    return 0;
}
