#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "bb64.h"

#define BUFSIZE	3

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        #ifdef DBG
            fprintf(stderr, "Error opening %s: %s\n", argv[1], strerror(errno));
        #endif
        return -1;
    }

    decode_b64(fd);

    return 0;
}

void decode_b64(int fd) {
    char buffer[BUFSIZ];

    while (read(fd, buffer, BUFSIZE) > 0) {
        for (int i = 0; i < BUFSIZE; i++)
            printf("%d - ", buffer[i] & 0x3F);
    }
}
