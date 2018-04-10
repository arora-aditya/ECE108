run: clean build
	./dice.o
	./cards.o

build:
	$(CXX) -fno-stack-protector -std=c++11 -g dice.cpp -o dice.o
	$(CXX) -fno-stack-protector -std=c++11 -g cards.cpp -o cards.o

clean:
	rm -f core *~ *~%~ *.o 
