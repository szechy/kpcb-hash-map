CC=gcc
CFLAGS += -O1 -g -Wall

all: shell test

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

shell: hash.o shell.o cfarmhash.o

test: hash.o test-cases.o cfarmhash.o unit-test-framework/unit_test_framework.o

clean:
	rm -rf *.o unit-test-framework/*.o *.dSYM shell test hash
