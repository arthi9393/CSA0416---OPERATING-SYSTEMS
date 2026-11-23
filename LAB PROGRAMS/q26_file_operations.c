/* Q26: File management operations (CO4)
   create, write, append, read, copy, rename, delete, file info */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_write(void) {
    char name[100], line[256];
    printf("File name: "); scanf("%99s", name);
    FILE *fp = fopen(name, "w");
    if (!fp) { perror("fopen"); return; }
    printf("Enter text (a single '.' on a line ends input):\n");
    getchar();
    while (fgets(line, sizeof line, stdin) && strcmp(line, ".\n") != 0) fputs(line, fp);
    fclose(fp);
    printf("File written.\n");
}
void append(void) {
    char name[100], line[256];
    printf("File name: "); scanf("%99s", name);
    FILE *fp = fopen(name, "a");
    if (!fp) { perror("fopen"); return; }
    printf("Enter text to append ('.' ends):\n");
    getchar();
    while (fgets(line, sizeof line, stdin) && strcmp(line, ".\n") != 0) fputs(line, fp);
    fclose(fp);
}
void read_file(void) {
    char name[100], line[256];
    printf("File name: "); scanf("%99s", name);
    FILE *fp = fopen(name, "r");
    if (!fp) { perror("fopen"); return; }
    printf("---- contents ----\n");
    while (fgets(line, sizeof line, fp)) fputs(line, stdout);
    fclose(fp);
}
void copy_file(void) {
    char src[100], dst[100]; int c;
    printf("Source file: "); scanf("%99s", src);
    printf("Destination file: "); scanf("%99s", dst);
    FILE *a = fopen(src, "rb"), *b = fopen(dst, "wb");
    if (!a || !b) { perror("fopen"); if (a) fclose(a); if (b) fclose(b); return; }
    while ((c = fgetc(a)) != EOF) fputc(c, b);
    fclose(a); fclose(b);
    printf("Copied.\n");
}
void rename_file(void) {
    char o[100], n[100];
    printf("Old name: "); scanf("%99s", o);
    printf("New name: "); scanf("%99s", n);
    if (rename(o, n) == 0) printf("Renamed.\n"); else perror("rename");
}
void delete_file(void) {
    char name[100];
    printf("File name: "); scanf("%99s", name);
    if (remove(name) == 0) printf("Deleted.\n"); else perror("remove");
}
void info(void) {
    char name[100]; struct stat st;
    printf("File name: "); scanf("%99s", name);
    if (stat(name, &st) == 0)
        printf("Size: %ld bytes, Permissions: %o, Links: %lu\n",
               (long)st.st_size, st.st_mode & 0777, (unsigned long)st.st_nlink);
    else perror("stat");
}

int main(void) {
    int ch;
    do {
        printf("\n--- FILE OPERATIONS ---\n1.Create/Write 2.Append 3.Read 4.Copy 5.Rename 6.Delete 7.Info 8.Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) break;
        switch (ch) {
            case 1: create_write(); break;
            case 2: append(); break;
            case 3: read_file(); break;
            case 4: copy_file(); break;
            case 5: rename_file(); break;
            case 6: delete_file(); break;
            case 7: info(); break;
            case 8: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 8);
    return 0;
}
