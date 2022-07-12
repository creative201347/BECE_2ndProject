#include <include/client.hpp>

void str_trim_lf(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    // we need 2 things: ip address and port number, in that order
    if (argc != 3)
    {
        std::cerr << RED << "Usage: ip_address port" << RESET << std::endl;
        exit(0);
    }

    // grab the IP address and port number
    char *serverIp = argv[1];
    int port = atoi(argv[2]);

    // create a message buffer
    char msg[1500];
    char name[50];

    std::cout << "Please enter your name: ";
    fgets(name, 32, stdin);
    str_trim_lf(name, strlen(name));
    if (strlen(name) > 32 || strlen(name) < 2)
    {
        std::cout << RED << "Name must be less than 30 and more than 2 characters" << RESET << std::endl;
        return EXIT_FAILURE;
    }

    // setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    memset(&sendSockAddr, 0, sizeof(sendSockAddr)); // clear the buffer
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // try to connect...
    int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0)
    {
        std::cout << RED << "Error connecting to socket!" << RESET << std::endl;
        exit(1);
    }

    std::cout << GRN << "Connected to the server!" << RESET << std::endl;
    send(clientSd, (char *)&name, strlen(name), 0);
    std::cout << CYN << "Welcome to our server!! " << RESET << std::endl;

    while (1)
    {
        std::cout << "Enter a message: ";
        std::string data;
        std::getline(std::cin, data);
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        strcpy(msg, data.c_str());
        if (data == "exit")
        {
            send(clientSd, (char *)&msg, strlen(msg), 0);
            break;
        }

        send(clientSd, (char *)&msg, strlen(msg), 0);
        std::cout << "Awaiting server response..." << std::endl;
        memset(&msg, 0, sizeof(msg)); // clear the buffer

        // Receiving message from server and displaying
        recv(clientSd, (char *)&msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit"))
        {
            std::cout << RED << "Server has quit the session" << RESET << std::endl;
            break;
        }
        std::cout << MAG << "Server: " << msg << RESET << std::endl;
    }

    close(clientSd);
    std::cout << RED << "Connection closed" << RESET << std::endl;
    std::cout << CYN << "Thank you for visiting!! " << RESET << std::endl;
    return 0;
}
