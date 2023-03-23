CFLAGS =-Wall

all: report

report: test_flagless test_o0 test_os test_o2
	echo Static flagless: > report.txt
	echo >> raport.txt
	cat results_static.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Shared flagless: >> report.txt
	echo >> raport.txt
	cat results_shared.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Dynamic flagless: >> report.txt
	echo >> raport.txt
	cat results_dynamic.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Static with -O0 flag: >> report.txt
	echo >> raport.txt
	cat results_static_o0.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Shared with -O0 flag: >> report.txt
	echo >> raport.txt
	cat results_shared_o0.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Dynamic with -O0 flag: >> report.txt
	echo >> raport.txt
	cat results_dynamic_o0.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Static with -Os flag: >> report.txt
	echo >> raport.txt
	cat results_static_os.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Shared with -Os flag: >> report.txt
	echo >> raport.txt
	cat results_shared_os.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Dynamic with -Os flag: >> report.txt
	echo >> raport.txt
	cat results_dynamic_os.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Static with -O2 flag: >> report.txt
	echo >> raport.txt
	cat results_static_o2.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Shared with -O2 flag: >> report.txt
	echo >> raport.txt
	cat results_shared_o2.txt >> report.txt
	echo >> raport.txt
	echo >> raport.txt

	echo Dynamic with -O2 flag: >> report.txt
	echo >> raport.txt
	cat results_dynamic_o2.txt >> report.txt


recompile:
	(cd ../zad2 && make clean && make OPT=$(OPT))

recompile_o0:
	make recompile OPT=-O0

recompile_os:
	make recompile OPT=-Os

recompile_o2:
	make recompile OPT=-O2

test_flagless: recompile test_static test_shared test_dynamic

test_o0: recompile_o0 test_static_o0 test_shared_o0 test_dynamic_o0

test_os: recompile_os test_static_os test_shared_os test_dynamic_os

test_o2: recompile_o2 test_static_o2 test_shared_o2 test_dynamic_o2

test_static:
	../zad2/repl_static < command_list.txt > results_static.txt

test_shared:
	../zad2/repl_shared < command_list.txt > results_shared.txt

test_dynamic:
	../zad2/repl_dynamic < command_list.txt > results_dynamic.txt

test_static_o0:
	../zad2/repl_static < command_list.txt > results_static_o0.txt

test_shared_o0:
	../zad2/repl_shared < command_list.txt > results_shared_o0.txt

test_dynamic_o0:
	../zad2/repl_dynamic < command_list.txt > results_dynamic_o0.txt

test_static_os:
	../zad2/repl_static < command_list.txt > results_static_os.txt

test_shared_os:
	../zad2/repl_shared < command_list.txt > results_shared_os.txt

test_dynamic_os:
	../zad2/repl_dynamic < command_list.txt > results_dynamic_os.txt

test_static_o2:
	../zad2/repl_static < command_list.txt > results_static_o2.txt

test_shared_o2:
	../zad2/repl_shared < command_list.txt > results_shared_o2.txt

test_dynamic_o2:
	../zad2/repl_dynamic < command_list.txt > results_dynamic_o2.txt

clean:
	rm recompile test* print 