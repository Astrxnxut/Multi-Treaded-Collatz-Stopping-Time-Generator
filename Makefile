mt-collatz: mt-collatz.o
	g++ -g -Wall mt-collatz.o -o mt-collatz

mt-collatz.o: mt-collatz.cpp
	g++ -g -Wall -c mt-collatz.cpp

clean:
	rm *.o mt-collatz
