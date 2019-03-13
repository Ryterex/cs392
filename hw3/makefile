CC=gcc
CFLAGS=-I.
DEPS = msh.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

msh: msh.o
	$(CC) -o msh msh.o