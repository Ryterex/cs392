CC=gcc
CFLAGS=-I.
DEPS = oocmerge.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oocmerge: oocmerge.o
	$(CC) -o oocmerge oocmerge.o