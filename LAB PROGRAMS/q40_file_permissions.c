/* Q40: Illustrate Linux file access permissions and types of users (CO4)
   Usage: ./q40_file_permissions [file]   (default: creates a demo file) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

static void show(const char *file) {
    struct stat st;
    if (stat(file, &st) < 0) { perror("stat"); return; }
    char p[11] = "----------";
    if (S_ISDIR(st.st_mode)) p[0] = 'd'; else if (S_ISLNK(st.st_mode)) p[0] = 'l';
    const char *rwx = "rwxrwxrwx";
    for (int i = 0; i < 9; i++) if (st.st_mode & (1 << (8 - i))) p[i + 1] = rwx[i];
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    printf("\nFile: %s\nMode string : %s  (octal %03o)\n", file, p, st.st_mode & 0777);
    printf("Owner (user): %s  -> %c%c%c\n", pw ? pw->pw_name : "?", p[1], p[2], p[3]);
    printf("Group       : %s  -> %c%c%c\n", gr ? gr->gr_name : "?", p[4], p[5], p[6]);
    printf("Others      : (everyone else)  -> %c%c%c\n", p[7], p[8], p[9]);
    printf("Access check for current user (uid %d): read=%s write=%s execute=%s\n", getuid(),
           access(file, R_OK) == 0 ? "yes" : "no",
           access(file, W_OK) == 0 ? "yes" : "no",
           access(file, X_OK) == 0 ? "yes" : "no");
}

int main(int argc, char *argv[]) {
    printf("=== Linux File Access Permissions ===\n");
    printf("Types of users : u = owner, g = group, o = others (a = all)\n");
    printf("Permissions    : r = read (4), w = write (2), x = execute (1)\n");
    printf("File types     : '-' regular, 'd' directory, 'l' symlink, 'c' char dev, 'b' block dev\n");
    printf("Special bits   : setuid (4000), setgid (2000), sticky (1000)\n");
    printf("Commands       : chmod, chown, chgrp, umask, ls -l, stat\n");

    if (argc > 1) { show(argv[1]); return 0; }

    const char *f = "perm_demo.txt";
    int fd = open(f, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }
    write(fd, "demo\n", 5); close(fd);

    mode_t modes[] = {0644, 0755, 0600, 0444, 0777};
    for (int i = 0; i < 5; i++) {
        chmod(f, modes[i]);
        printf("\n>>> chmod %03o %s", modes[i], f);
        show(f);
    }
    printf("\nCurrent umask: ");
    mode_t um = umask(0); umask(um);
    printf("%03o  (new files get 666 & ~umask = %03o, new dirs 777 & ~umask = %03o)\n", um, 0666 & ~um, 0777 & ~um);
    unlink(f);
    return 0;
}
