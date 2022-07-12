#include <iostream>

int main()
{
    std::string name;

    std::cout << "Enter your name in cin mode: ";
    std::cin >> name;
    std::cout << name << std::endl;

    // std::cout << "Enter your name in getline mode: ";
    // std::getline(std::cin, name);
    // std::cout << name << std::endl;
    return 0;
}
