CFLAGS =-Wall


all: prog

prog: prog.o
	gcc $(CFLAGS) -o prog prog.o

prog.o: prog.c
	gcc $(CFLAGS) -c prog.c

clean:
	rm *.o prog