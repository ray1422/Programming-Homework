#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#define BUF_SIZE 4096


int main(int argc, char* argv[]) {
    int inputFd, outputFd;
    ssize_t numIn, numOut;
    char buffer[BUF_SIZE];
    if (argc != 3) {
        char* filename=basename(argv[0]);
        fprintf(stderr, "usage: %s <src> <dst>\n", filename);
        exit(EXIT_FAILURE);
    }

    inputFd = open (argv [1], O_RDONLY);
    if (inputFd == -1) {
        char* filename=basename(argv[1]);
        char errmsg[1024];
        sprintf(errmsg, "無法開啟來源檔案 (%s)", filename);
        perror (errmsg); 
        exit(1); 
    }

    outputFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR| S_IWUSR);
    if(outputFd == -1){
        char* filename=basename(argv[3]);
        char errmsg[1024];
        sprintf(errmsg, "無法打開目的檔案 (%s)", filename);
        perror (errmsg); 
        exit(1); 
    }

    off_t data_off=0, hole_off=0, cur_off=0;
    long long fileSize, blockSize, pos=0;
    fileSize = lseek(inputFd, 0, SEEK_END);
    lseek(inputFd, 0, SEEK_SET);

    while (1) {
        cur_off = lseek(inputFd, cur_off, SEEK_DATA);
        data_off = cur_off;
        cur_off = lseek(inputFd, cur_off, SEEK_HOLE);
        hole_off = cur_off;
        if (data_off > hole_off) {
            continue;
        }
        blockSize=hole_off-data_off;
        lseek(inputFd, data_off, SEEK_SET);
        lseek(outputFd, data_off, SEEK_SET);
        while((numIn = read (inputFd, buffer, BUF_SIZE)) > 0) {
            numOut = write (outputFd, buffer, (ssize_t) numIn);
            if (numIn != numOut) perror("numIn != numOut");
            blockSize-=numIn;
            if (blockSize == 0) break;
        }
        if (lseek(outputFd, 0, SEEK_CUR) == fileSize) break;
    }
    close (inputFd);
    close (outputFd);

    return EXIT_SUCCESS;
}

