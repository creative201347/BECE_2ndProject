#include <include/server.hpp>

int main(int argc, char *argv[])
{
    // for the server, we only need to specify a port number
    if (argc != 2)
    {
        std::cerr << RED << "Usage: port" << RESET << std::endl;
        exit(0);
    }

    // grab the port number
    int port = atoi(argv[1]);

    // buffer to send and receive messages with
    char msg[1500];
    char client[50];

    // setup a socket and connection tools
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr)); // clear the buffer
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    // open stream oriented socket with internet address
    // also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        std::cerr << RED << "Error establishing the server socket" << RESET << std::endl;
        exit(0);
    }

    // bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (bindStatus < 0)
    {
        std::cerr << RED << "Error binding socket to local address" << RESET << std::endl;
        exit(0);
    }

    // listen for up to 5 requests at a time
    std::cout << "Waiting for  client to connect..." << std::endl;
    listen(serverSd, 5);

    // receive a request from client using accept
    // we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // accept, create a new socket descriptor to
    // handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (newSd < 0)
    {
        std::cerr << RED << "Error accepting request from client!" << RESET << std::endl;
        exit(1);
    }
    std::cout << GRN << "Connected with client!" << RESET << std::endl;

    // receive client's name
    memset(&client, 0, sizeof(client)); // clear the buffer
    recv(newSd, (char *)&client, sizeof(client), 0);
    std::cout << GRN << client << " has joined the socket" << RESET << std::endl;

    while (1)
    {
        std::cout << "Awaiting client response..." << std::endl;
        memset(&msg, 0, sizeof(msg)); // clear the buffer

        // receive a message from the client (listen)
        recv(newSd, (char *)&msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit"))
        {
            std::cout << RED << "Client has quit the session" << RESET << std::endl;
            break;
        }
        std::cout << BLU << client << ": " << msg << RESET << std::endl;

        std::cout << "Enter a message: ";
        std::string data;
        std::getline(std::cin, data);
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        strcpy(msg, data.c_str());
        if (data == "exit")
        {
            // send to the client that server has closed the connection
            send(newSd, (char *)&msg, strlen(msg), 0);
            break;
        }
        // send the message to client
        send(newSd, (char *)&msg, strlen(msg), 0);
    }
    close(newSd);
    close(serverSd);

    std::cout << RED << "Connection closed..." << RESET << std::endl;
    std::cout << CYN << "Thank you for visiting!! " << RESET << std::endl;

    return 0;
}