#include <iostream>
#include <sys/socket.h>
#include <netdb.h>

struct hostent *host;
char *serverIp = "127.0.0.1";

int main()
{
    host = gethostbyname(serverIp);
    std::cout << host << std::endl;
    return 0;
}
// gethostbyname() takes a string like "www.yahoo.com", and returns a struct hostent which contains tons of information,
// including the IP address. (Other information is the official host name, a list of aliases, the address type,
// the length of the addresses, and the list of addresses--it's a general-purpose structure that's pretty easy
// to use for our specific purposes once you see how.)

// The gethostbyname() function of the C programming language is used to resolve a hostname into all those
// characteristics with which this host can be identified over a network