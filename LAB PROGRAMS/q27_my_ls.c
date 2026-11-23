/* Q27: Simulate the UNIX ls command (CO5)
   Usage: ./q27_my_ls [-a] [-l] [directory]  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

static int cmp(const void *a, const void *b) {
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static void print_long(const char *dir, const char *name) {
    char path[1024], perm[11], tm[32];
    struct stat st;
    snprintf(path, sizeof path, "%s/%s", dir, name);
    if (lstat(path, &st) < 0) { perror(path); return; }
    strcpy(perm, "----------");
    if (S_ISDIR(st.st_mode)) perm[0] = 'd';
    else if (S_ISLNK(st.st_mode)) perm[0] = 'l';
    else if (S_ISCHR(st.st_mode)) perm[0] = 'c';
    else if (S_ISBLK(st.st_mode)) perm[0] = 'b';
    const char *rwx = "rwxrwxrwx";
    for (int i = 0; i < 9; i++) if (st.st_mode & (1 << (8 - i))) perm[i + 1] = rwx[i];
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    strftime(tm, sizeof tm, "%b %d %H:%M", localtime(&st.st_mtime));
    printf("%s %2lu %-8s %-8s %8ld %s %s\n", perm, (unsigned long)st.st_nlink,
           pw ? pw->pw_name : "?", gr ? gr->gr_name : "?", (long)st.st_size, tm, name);
}

int main(int argc, char *argv[]) {
    int all = 0, lng = 0, i;
    const char *dir = ".";
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strchr(argv[i], 'a')) all = 1;
            if (strchr(argv[i], 'l')) lng = 1;
        } else dir = argv[i];
    }
    DIR *d = opendir(dir);
    if (!d) { perror(dir); return 1; }
    char *names[4096]; int n = 0;
    struct dirent *e;
    while ((e = readdir(d)) != NULL && n < 4096) {
        if (!all && e->d_name[0] == '.') continue;
        names[n++] = strdup(e->d_name);
    }
    closedir(d);
    qsort(names, n, sizeof(char *), cmp);
    for (i = 0; i < n; i++) {
        if (lng) print_long(dir, names[i]);
        else printf("%s%s", names[i], (i == n - 1) ? "\n" : "  ");
        free(names[i]);
    }
    return 0;
}
