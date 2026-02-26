#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <file.h>
#include <gcc.h>

#define exit(...) return _VA_ARGS_

#define BUF_SIZE 512

char buf[BUF_SIZE];

int main(int argc, char *argv[])
{
    int fd;
    int n;
    int i;

    if (argc < 2) {
        printf("Usage: cat <filename>\n");
        return -1;
    }

    for (i = 1; i < argc; i++) {

        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            printf("cat: cannot open %s\n", argv[i]);
            continue;
        }

        while ((n = read(fd, buf, BUF_SIZE)) > 0) {
            write(1, buf, n);   // 1 = stdout
        }

        close(fd);
    }

    return 0;
}
