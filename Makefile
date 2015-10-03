CC=gcc
CFLAGS += -O1 -g -Wall

all: shell test

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: hash.o shell.o

test: hash.o test.o

clean:
	rm -rf *.o *.dSYM shell test
