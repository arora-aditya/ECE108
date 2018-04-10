run: main
	./main ../../samples/test*
fulltest: main
	./main ../../samples/*

main: main.o ../dimacs/dimacs_reader.o
	g++ -o main main.o ../dimacs/dimacs_reader.o

main.o: main.cpp ../../inc/dimacs_reader.h
	g++ -c main.cpp -I ../../inc

clean:
	rm -f main *.o
