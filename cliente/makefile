cliente: main.o
	g++ -Wall -Werror main.o -o cliente

main.o: main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -rf *o main

kill:
	pkill -9 cliente