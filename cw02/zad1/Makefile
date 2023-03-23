CFLAGS =-Wall


all: prog_lib prog_sys pomiar_zad_1.txt

pomiar_zad_1.txt: prog_lib prog_sys Makefile
	touch pomiar_zad_1.txt
	echo "PROG_LIB:" > pomiar_zad_1.txt
	./prog_lib a o test_input.txt test_output.txt >> pomiar_zad_1.txt
	echo >> pomiar_zad_1.txt
	echo "PROG_SYS:" >> pomiar_zad_1.txt
	./prog_sys a o test_input.txt test_output.txt >> pomiar_zad_1.txt

prog_lib: prog_lib.o
	gcc $(CFLAGS) -o prog_lib prog_lib.o

prog_sys: prog_sys.o
	gcc $(CFLAGS) -o prog_sys prog_sys.o

prog_lib.o: prog_lib.c
	gcc $(CFLAGS) -c prog_lib.c

prog_sys.o: prog_sys.c
	gcc $(CFLAGS) -c prog_sys.c

clean:
	rm *.o prog_lib prog_sys pomiar_zad_1.txt