all:	lcs floyd

lcs:	lcs.o
	g++ -O0 -g -Wall -std=c++11  lcs.o -o lcs

lcs.o:	lcs.cpp
	g++ -O0 -g -Wall -std=c++11 -c lcs.cpp

testl:	lcs
	./lcs qtrenm qwertyuiopasdfghjklzxcvbnm 
	./lcs qwertyuiopasdfghjklzxcvbnm qtrenm 
	./lcs cat dog
	./lcs aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbba
	
floyd:	floyd.o
	g++ -O0 -g -Wall -std=c++11  floyd.o -o floyd

floyd.o:	floyd.cpp
	g++ -O0 -g -Wall -std=c++11 -c floyd.cpp


testf:	floyd
	./floyd

clean:
	rm -f *.o lcs floyd

valgl:	lcs
	valgrind ./lcs cat caet

valgf:	floyd
	valgrind ./floyd
