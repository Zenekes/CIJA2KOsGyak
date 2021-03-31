#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    int fd;
    char *buf[100];
    int len;

    if ((fd = open("CIJA2K.txt", O_RDWR)) < 0) {
        perror("open hiba");
        return -1;
    }

    if ((len = read(fd, buf, sizeof(buf))) != 0) {
        if (len == -1 && errno != EINTR) {
            perror("read hiba");
            return -1;
        }
        int index;
        for (index = 0; index < sizeof(buf) && buf[index] != EOF; index++);
        buf[index] = '\0';
        printf("Beolvasva: %d byte\n Tartalma: %s\n", len, buf);
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("lseek hiba");
        return -1;
    }
    printf("Pozicio a fajl elejere mozgatva\n");

    if ((len = write(fd, "Hello World", 11)) != 11) {
        perror("write hiba");
        return -1;
    }
    printf("%d byte kiírva\n", len);

    close(fd);
    return 0;
}
