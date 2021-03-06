#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define ENC_BATCH 3
#define DEC_BATCH 4

char* b64_dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_b64(int);
void decode_b64(int);
unsigned int flip_buffer(unsigned int);
int is_little_endian(void);

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-d | -e] <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[argc - 1], O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "Error opening %s: %s\n", argv[argc - 1], strerror(errno));
        return -1;
    }

    if (!strcmp(argv[1], "-d"))
        decode_b64(fd);
    else if (!strcmp(argv[1], "-e") || argc == 2)
        encode_b64(fd);
    else {
        fprintf(stderr, "Usage: %s [-d | -e] <filename>\n", argv[0]);
        return -1;
    }

    return 0;
}

void encode_b64(int fd) {
    unsigned int buffer = 0;
    int i, redb, offset, little_endian = is_little_endian();

    while((redb = read(fd, &buffer, ENC_BATCH))) {
        if (little_endian)
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

void decode_b64(int fd) {
    char buffer[DEC_BATCH];
    unsigned int int_buffer = 0, base_value;
    int i, redb, padding = 0;

    while((redb = read(fd, buffer, DEC_BATCH))) {
        // Trailing '\n'...
        if (redb != DEC_BATCH)
            continue;

        for (i = 0; i < DEC_BATCH; i++) {
            if (buffer[i] != '=') {
                base_value = ((unsigned int) (strchr(b64_dict, buffer[i]) - b64_dict) & 0x3F);
                int_buffer |= base_value << (26 - i  * 6);
                #ifdef DBG
                    printf("Iteration %d\n\tORed value = %d [0x%X]\n\tShift = %d\n", i, base_value, base_value, (26 - i  * 6));
                #endif
            }
            else
                padding++;
        }

        for (i = 0; i < (3 - padding); i++)
            printf("%c", (int_buffer & 0xFF << (24 - i * 8)) >> (24 - i * 8));

        int_buffer = padding = 0;
    }
}

unsigned int flip_buffer(unsigned int foo) {
    int i, tmp = 0;
    for (i = 0; i < (int) sizeof(unsigned int); i++)
        tmp |= ((foo & 0xFF << (i * 8)) >> (i * 8)) << ((3 - i) * 8);
    return tmp;
}

int is_little_endian(void) {
    int x = 1;
    return (int) *((char*) &x);
}
