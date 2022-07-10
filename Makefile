compile:
	g++ -o server.o src/server.cpp -I.
	g++ -o client.o src/client.cpp -I.

server:
	./server.o 4000

client:
	./client.o 127.0.0.1 4000

clean:
	rm -f client.o server.o