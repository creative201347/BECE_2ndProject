compile:
	g++ -o server.o src/server.cpp -I/include
	g++ -o client.o src/client.cpp -I/include

server:
	./server.o 8080

client:
	./client.o 127.0.0.1 8080

clean:
	rm -f client.o server.o