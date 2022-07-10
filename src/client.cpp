#include <include/client.hpp>

void str_trim_lf(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    { // trim \n
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

// using namespace std;
int main(int argc, char *argv[])
{
    // we need 2 things: ip address and port number, in that order
    if (argc != 3)
    {
        std::cerr << "Usage: ip_address port" << std::endl;
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
        printf("Name must be less than 30 and more than 2 characters.\n");
        return EXIT_FAILURE;
    }

    // setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // try to connect...
    int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0)
    {
        std::cout << "Error connecting to socket!" << std::endl;
        exit(1);
    }
    std::cout << "Connected to the server!" << std::endl;
    send(clientSd, (char *)&name, strlen(name), 0);
    std::cout << "WELCOME TO THE CHATROOM " << std::endl;

    // int bytesRead, bytesWritten = 0;
    // struct timeval start1, end1;
    // gettimeofday(&start1, NULL);

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

        // bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);
        send(clientSd, (char *)&msg, strlen(msg), 0);
        std::cout << "Awaiting server response..." << std::endl;
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        // bytesRead += recv(clientSd, (char *)&msg, sizeof(msg), 0);
        recv(clientSd, (char *)&msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit"))
        {
            std::cout << "Server has quit the session" << std::endl;
            break;
        }
        std::cout << "Server: " << msg << std::endl;
    }
    // gettimeofday(&end1, NULL);
    // close(clientSd);
    // std::cout << "********Session********" << std::endl;
    // std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << std::endl;
    // std::cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
    //      << " secs" << std::endl;
    std::cout << "Connection closed" << std::endl;
    return 0;
}
