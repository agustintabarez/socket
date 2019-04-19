servidor: MensajeEnviado.o main.o
	g++ -Wall -o servidor MensajeEnviado.o main.o

main.o: main.cpp
	g++ -Wall -c main.cpp
	
MensajeEnviado.o: ./nodos/MensajeEnviado/MensajeEnviado.cpp ./nodos/MensajeEnviado/MensajeEnviado.h
	g++ -Wall -c ./nodos/MensajeEnviado/MensajeEnviado.cpp

clean:
	rm -rf *o main