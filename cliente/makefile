cliente: MensajeRecibido.o main.o
	g++ -Wall -o cliente MensajeRecibido.o main.o

main.o: main.cpp
	g++ -Wall -c main.cpp

MensajeRecibido.o: ./nodos/MensajeRecibido/MensajeRecibido.cpp ./nodos/MensajeRecibido/MensajeRecibido.h
	g++ -Wall -c ./nodos/MensajeRecibido/MensajeRecibido.cpp

clean:
	rm -rf *o main

kill:
	pkill -9 cliente