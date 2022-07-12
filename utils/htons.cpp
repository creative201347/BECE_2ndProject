// htons() — Translate an unsigned short integer into network byte order

#include <iostream>
#include <arpa/inet.h>

int main()
{
    int port = 4000;
    in_port_t p;
    p = htons(port);
    std::cout << p << std::endl;
    return 0;
}