CFLAGS =-Wall


all: main_static main_shared

wclib_static.o: wclib.c wclib.h
	gcc $(CFLAGS) -c -o wclib_static.o wclib.c

wclib_shared.o: wclib.c wclib.h
	gcc $(CFLAGS) -fPIC -c -o wclib_shared.o wclib.c

libwclib.a: wclib_static.o
	ar rcs libwclib.a wclib_static.o

libwclib.so: wclib_shared.o
	gcc $(CFLAGS) -shared -fPIC -o libwclib.so wclib_shared.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

main_static: libwclib.a main.o
	gcc $(CFLAGS) -static -o main_static main.o -L. -lwclib

main_shared: libwclib.so main.o
	gcc $(CFLAGS) -o main_shared main.o -L. -lwclib -Wl,-rpath,.

clean:
	rm -f *.o libwclib.a libwclib.so main*
