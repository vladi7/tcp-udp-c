#
# Makefile
#
all:	udp

udp:	UDPserver UDPclient

client.o server.o: inet.h

UDPserver: server.o 
	gcc -g -o UDPserver server.o

UDPclient: client.o 
	gcc -g -o UDPclient client.o 

#
# Clean up the mess we made
#
clean:
	rm *.o \
	UDPserver UDPclient
 
