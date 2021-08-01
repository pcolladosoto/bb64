# Note make will substitue non-defined variables with an empty string!
CC = gcc
CFLAGS = -Wall -Wextra
# LDFLAGS = -lm
PROGS = bb64
TRASH = *.o

# Enable debugging output
# DBGFLAGS = -DDBG

all: $(PROGS)

bb64: bb64.o
	$(CC) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(DBGFLAGS)

.PHONY: test clean

test: all
	bash tests/run_tests.sh

clean:
	rm -f $(PROGS) $(TRASH)
