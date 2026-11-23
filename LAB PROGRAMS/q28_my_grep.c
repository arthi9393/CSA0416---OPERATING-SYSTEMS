/* Q28: Simulate the UNIX grep command (CO5)
   Usage: ./q28_my_grep [-i] [-n] [-v] [-c] pattern file...  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *find(const char *line, const char *pat, int icase) {
    if (!icase) return strstr(line, pat);
    size_t pl = strlen(pat);
    for (const char *p = line; *p; p++) {
        size_t k = 0;
        while (k < pl && p[k] && tolower((unsigned char)p[k]) == tolower((unsigned char)pat[k])) k++;
        if (k == pl) return (char *)p;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int icase = 0, num = 0, inv = 0, cnt = 0, i = 1;
    for (; i < argc && argv[i][0] == '-'; i++) {
        if (strchr(argv[i], 'i')) icase = 1;
        if (strchr(argv[i], 'n')) num = 1;
        if (strchr(argv[i], 'v')) inv = 1;
        if (strchr(argv[i], 'c')) cnt = 1;
    }
    if (argc - i < 2) {
        fprintf(stderr, "Usage: %s [-i] [-n] [-v] [-c] pattern file...\n", argv[0]);
        return 1;
    }
    const char *pat = argv[i++];
    int multi = (argc - i) > 1;
    char line[4096];
    for (; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) { perror(argv[i]); continue; }
        int ln = 0, matches = 0;
        while (fgets(line, sizeof line, fp)) {
            ln++;
            int hit = find(line, pat, icase) != NULL;
            if (hit == !inv) {
                matches++;
                if (!cnt) {
                    if (multi) printf("%s:", argv[i]);
                    if (num) printf("%d:", ln);
                    fputs(line, stdout);
                    if (line[strlen(line) - 1] != '\n') putchar('\n');
                }
            }
        }
        if (cnt) { if (multi) printf("%s:", argv[i]); printf("%d\n", matches); }
        fclose(fp);
    }
    return 0;
}
