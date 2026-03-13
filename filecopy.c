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
