

all:	tcp 

tcp:	server client 

client.o server.o: inet.h

server:	server.o 
	gcc -g -ansi -pedantic -o TCPserver server.o

client:	client.o 
	gcc -g -ansi -pedantic -o TCPclient client.o


clean:
	rm *.o \
	TCPserver TCPclient
 
