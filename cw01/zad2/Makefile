CFLAGS =-Wall


all: repl_static repl_shared repl_dynamic

wcrepl.o: wcrepl.c
	gcc $(CFLAGS) $(OPT) -c wcrepl.c

repl_static: wcrepl.o
	(cd ../zad1 && make libwclib.a)
	gcc $(CFLAGS) $(OPT) -static -o repl_static wcrepl.o -L../zad1/ -lwclib

repl_shared: wcrepl.o
	(cd ../zad1 && make libwclib.so)
	gcc $(CFLAGS) $(OPT) -o repl_shared wcrepl.o -L../zad1/ -lwclib -Wl,-rpath,../zad1/

repl_dynamic: wcrepl.c
	(cd ../zad1 && make libwclib.so)
	gcc $(CFLAGS) $(OPT) -o repl_dynamic wcrepl.c -ldl -D DYNAMIC

clean:
	rm -f wcrepl.o repl_*