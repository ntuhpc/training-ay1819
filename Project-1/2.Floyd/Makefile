CC = gcc

all: test

test: APSPtest.o MatUtil.o Floyd_openMP.o
	$(CC) -fopenmp -o $@ $?

%.o: %.c
	$(CC) -fopenmp -std=c99 -c $<

clean:
	rm *.o test
