CFLAGS =-Wall


all: prog_one prog_kilo pomiar_zad_2.txt

pomiar_zad_2.txt: prog_one prog_kilo Makefile
	touch pomiar_zad_2.txt
	echo "PROG_ONE_BYTE_AT_A_TIME:" > pomiar_zad_2.txt
	./prog_one test_input.txt test_output.txt >> pomiar_zad_2.txt
	echo >> pomiar_zad_2.txt
	echo "PROG_1K_BYTES_AT_A_TIME:" >> pomiar_zad_2.txt
	./prog_kilo test_input.txt test_output.txt >> pomiar_zad_2.txt

prog_one: prog_one.o Makefile
	gcc $(CFLAGS) -o prog_one prog_one.o

prog_kilo: prog_kilo.o Makefile
	gcc $(CFLAGS) -o prog_kilo prog_kilo.o

prog_one.o: prog_one.c
	gcc $(CFLAGS) -c prog_one.c

prog_kilo.o: prog_kilo.c
	gcc $(CFLAGS) -c prog_kilo.c

clean:
	rm *.o prog_one prog_kilo pomiar_zad_2.txt