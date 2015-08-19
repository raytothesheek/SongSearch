
SongSearch.out: mynew.o SearchRunner.o SongSearch.o QuadraticProbing.o
	g++ -ansi -Wall -g -o SongSearch.out mynew.o SearchRunner.o SongSearch.o QuadraticProbing.o

mynew.o: mynew.cpp mynew.h 
	g++ -ansi -Wall -g -c mynew.cpp

SearchRunner.o: SearchRunner.cpp CPUTimer.h mynew.h SearchRunner.h SongSearch.h 
	g++ -ansi -Wall -g -c SearchRunner.cpp

SongSearch.o: SongSearch.cpp  SongSearch.h SearchRunner.h mynew.h
	g++ -ansi -Wall -g -c SongSearch.cpp 

QuadraticProbing.o: QuadraticProbing.cpp QuadraticProbing.h mystring.h vector.h
	g++ -ansi -Wall -g -c QuadraticProbing.cpp

clean: 
	rm -f SongSearch.out mynew.o  SearchRunner.o  SongSearch.o QuadraticProbing.o
