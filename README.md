# Linux-File-IO-Systems-locking
Ex07-Linux File-IO Systems-locking
# AIM:
To Write a C program that illustrates files copying and locking

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux IO Systems locking

### Step 3:

Execute the C Program for the desired output. 

# PROGRAM:

## 1.To Write a C program that illustrates files copying 
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int in, out;
    int nread;
    char buffer[1024];

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    /* Open source file */
    in = open(argv[1], O_RDONLY);
    if (in < 0) {
        perror("Error opening source file");
        exit(1);
    }

    /* Open destination file */
    out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (out < 0) {
        perror("Error opening destination file");
        close(in);
        exit(1);
    }

    /* Copy file contents */
    while ((nread = read(in, buffer, sizeof(buffer))) > 0) {
        write(out, buffer, nread);
    }

    if (nread < 0) {
        perror("Error reading file");
    }

    /* Close files */
    close(in);
    close(out);

    printf("File copied successfully\n");

    return 0;
}






## 2.To Write a C program that illustrates files locking
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

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    char *file = argv[1];
    int fd;

    printf("Opening %s\n", file);

    fd = open(file, O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    if (flock(fd, LOCK_SH) == -1) {
        perror("Error acquiring shared lock");
        close(fd);
        exit(1);
    }

    printf("Acquired shared lock using flock\n");
    display_lslocks();

    sleep(2);

    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("Error upgrading to exclusive lock");
        flock(fd, LOCK_UN);
        close(fd);
        exit(1);
    }

    printf("Acquired exclusive lock using flock\n");
    display_lslocks();

    sleep(2);

    if (flock(fd, LOCK_UN) == -1) {
        perror("Error unlocking");
        close(fd);
        exit(1);
    }

    printf("Unlocked\n");
    display_lslocks();

    close(fd);
    return 0;
}



## OUTPUT
![image](<image/Screenshot at 2026-03-25 08-48-22.png>)
![image](<image/Screenshot at 2026-03-13 17-21-35.png>)




# RESULT:
The programs are executed successfully.
