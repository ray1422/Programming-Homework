#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    FILE *fpi = freopen(argv[1], "r", stdin);
    int fd = open(argv[1], O_RDWR);
    if (fpi == NULL || fd < 0) {
        perror("");
        return 1;
    }
    int c;
    while ((c = getchar()) != EOF) {
        char cc = (char)tolower(c);
        write(fd, &cc, 1);
    }
    fclose(fpi); 
    close(fd); 
}
