CC = g++
RM = rm -f
CPPFLAGS = -I.
OBJECT_FILES = server.o client.o

compile: $(OBJECT_FILES)
	$(CC) -o server server.o
	$(CC) -o client client.o 

server.o: src/server.cpp include/server.hpp
	$(CC) -o server.o -c src/server.cpp $(CPPFLAGS)

client.o: src/client.cpp include/client.hpp
	$(CC) -o client.o -c src/client.cpp $(CPPFLAGS)

host:
	./server 4000

join:
	./client 127.0.0.1 4000

clean:
	rm -f *.o server client	