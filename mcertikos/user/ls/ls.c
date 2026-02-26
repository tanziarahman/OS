#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define DIRSIZ 14

struct dirent {
    short inum;
    char name[DIRSIZ];
};

void ls(char *path)
{
    int fd;
    struct dirent de;

    if ((fd = open(path, O_RDONLY)) < 0) {
        printf("ls: cannot open %s\n", path);
        return;
    }

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        printf("%s\n", de.name);
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        ls(".");  // default: current directory
    } else {
        for (int i = 1; i < argc; i++)
            ls(argv[i]);
    }

    return 0;
}