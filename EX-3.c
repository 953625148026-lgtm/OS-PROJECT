#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define BUF_SIZE 1024
 
int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    ssize_t n_read;
    char buffer[BUF_SIZE];
    char src_name[100], dest_name[100];
 
    if (argc == 3) {
        /* file names supplied on command line */
        snprintf(src_name, sizeof(src_name), "%s", argv[1]);
        snprintf(dest_name, sizeof(dest_name), "%s", argv[2]);
    } else {
        printf("Enter source file name: ");
        scanf("%99s", src_name);
        printf("Enter destination file name: ");
        scanf("%99s", dest_name);
    }
 
    /* Open source file in read-only mode */
    src_fd = open(src_name, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }
 
    /* Create/open destination file in write mode with rw-r--r-- permission */
    dest_fd = open(dest_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        exit(1);
    }
 
    /* Read from source and write to destination in chunks */
    while ((n_read = read(src_fd, buffer, BUF_SIZE)) > 0) {
        if (write(dest_fd, buffer, n_read) != n_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }
 
    if (n_read < 0)
        perror("Error reading source file");
    else
        printf("File '%s' copied to '%s' successfully.\n", src_name, dest_name);
 
    close(src_fd);
    close(dest_fd);
    return 0;
}
OUTPUT:
