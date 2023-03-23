CFLAGS =-Wall

all: report

report: test_static test_shared test_dynamic
	echo Static: > report.txt
	echo >> raport.txt
	cat results_static.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Shared: >> report.txt
	echo >> raport.txt
	cat results_shared.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Dynamic: >> report.txt
	echo >> raport.txt
	cat results_dynamic.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

recompile:
	(cd ../zad2 && make clean && make)

test_static:
	../zad2/repl_static < command_list.txt > results_static.txt

test_shared:
	../zad2/repl_shared < command_list.txt > results_shared.txt

test_dynamic:
	../zad2/repl_dynamic < command_list.txt > results_dynamic.txt

clean:
	rm recompile test* print