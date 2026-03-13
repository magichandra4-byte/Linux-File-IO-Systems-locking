#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

void display_lslocks() {
    printf("\nCurrent lslocks output:\n");
    fflush(stdout);
    system("lslocks");
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd;
    char *file = argv[1];

    printf("Opening file: %s\n", file);

    /* Open or create file */
    fd = open(file, O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    /* Acquire shared lock */
    if (flock(fd, LOCK_SH) == -1) {
        perror("Error acquiring shared lock");
        close(fd);
        exit(1);
    }

    printf("Shared lock acquired\n");
    display_lslocks();

    sleep(2);

    /* Upgrade to exclusive lock */
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("Error upgrading to exclusive lock");
        flock(fd, LOCK_UN);
        close(fd);
        exit(1);
    }

    printf("Exclusive lock acquired\n");
    display_lslocks();

    sleep(2);

    /* Unlock file */
    if (flock(fd, LOCK_UN) == -1) {
        perror("Error unlocking");
        close(fd);
        exit(1);
    }

    printf("File unlocked\n");
    display_lslocks();

    close(fd);
    return 0;
}
