CC = gcc
CFLAGS = -g -Wall -std=c11
LDLIBS = -lcs50

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(basename $(wildcard *.c))