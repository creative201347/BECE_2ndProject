# Client-Server chat in C++ using sockets

In this tutorial, I’ll demonstrate a simple Linux socket program that uses sockets to create a chat between a client and server. Before you read further into this, I recommend reading up on Linux socket programming and a bit on the layers of the internet for background. As this program uses Linux system calls, again, its best to have background on that as well.

Essentially, this program will be a mock instant messaging program that will communicate over TCP using sockets. The client will connect to the server through an IP address specified. The server will listen for up to 5 requests at a time. Afterwards, the server will accept the request to connect from a client and messages will be sent back and forth through a buffer. Should either the client or server decide to stop, at the end we close the sockets and terminate the program.

https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

## Socket Programming in C/C++: Handling multiple clients on server without multi threading

./client 127.0.0.1 8080
./server 8080
