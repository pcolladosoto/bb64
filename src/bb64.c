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

    encode_b64(fd);

    return 0;
}

void encode_b64(int fd) {
    // Careful with ENDIANNESS...
    unsigned int buffer = 0;

    int i, redb, offset;

    while((redb = read(fd, &buffer, BUFSIZE))) {
        buffer = flip_buffer(buffer);
        #ifdef DBG
            printf("* DBGB *\n");
            for (i = 24; i > 0; i -= 8)
                printf("\t%c [%X]\n", (buffer & (0xFF << i)) >> i, (buffer & (0xFF << i)) >> i);
            printf("* DBGE *\n");
        #endif

        for (i = 0; i < 4; i++) {
            if (i <= redb) {
                offset = (buffer & (0x3F << (26 - i * 6))) >> (26 - i * 6);
                printf("%c", b64_dict[offset]);
            }
            else
                printf("=");
        }

        buffer = 0;
    }
    printf("\n");
}

unsigned int flip_buffer(unsigned int foo) {
    int i, tmp = 0;
    for (i = 0; i < (int) sizeof(unsigned int); i++)
        tmp |= ((foo & 0xFF << (i * 8)) >> (i * 8)) << ((3 - i) * 8);
    return tmp;
}