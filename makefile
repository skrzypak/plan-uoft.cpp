kompilator=g++
standard=-std=c++17
optymalizacja=-O3
errors=-pedantic-errors
debug=
profilowanie=-pg
memory=memory/nvwa
type=release

.PHONY: clean

__ : $(type)/program
	./$(type)/program -i source-file/SF50.txt
	
$(type)/program : $(type)/main.o $(type)/functions.o $(type)/debug_new.o $(type)/static_mem_pool.o $(type)/mem_pool_base.o $(type)/bool_array.o $(type)/static_mem_pool.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ 

$(type)/main.o : cpp/main.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 
	            
$(type)/functions.o : cpp/functions.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 
	
$(type)/debug_new.o : $(memory)/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 
	
$(type)/static_mem_pool.o : $(memory)/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 		

$(type)/mem_pool_base.o : $(memory)/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 		

$(type)/bool_array.o : $(memory)/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 	

clean : 	
	for f in `ls *.o *~ ` ; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
	if [ -d html ] ; then rm -r html; fi ;
