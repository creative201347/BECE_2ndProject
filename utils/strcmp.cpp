#include <iostream>
#include <string.h>

int main()
{
    char msg[] = "exit";
    int result = strcmp(msg, "exit");

    if (result)
    {
        std::cout << "EXIT" << std::endl;
    }
    else
    {
        std::cout << "STAYS" << std::endl;
    }
    std::cout << result << std::endl;

    return 0;
}