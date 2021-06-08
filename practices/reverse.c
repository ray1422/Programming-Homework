#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
char buf[8192];
int main(int argc, char *argv[]) {
    int fi = open(argv[1], O_RDWR);
    int fd = open(argv[1], O_RDWR);
    if (fi < 0 || fd < 0) {
        perror("");
        return 1;
    }
    int c;
    while (1) {
        for (int i = 0;; i++) { 
            if (read(fi, buf+i, 1) <= 0) {buf[i] = '\0'; break;}
            buf[i+1] = '\0';
            if (buf[i] == '\n') break;
        }
        puts(buf);
        if (strlen(buf) == 0) break;
        for (int i = strlen(buf) - 1; i >= 0; i--) {
            if (buf[i] == '\n') continue;
            write(fd, buf+i, 1);
        }
        char cc = '\n';
        write(fd, &cc, 1);

    }
END:
    close(fi); 
    close(fd); 
}
