#include <iostream>
#include <stdlib.h>

int main()
{
    char str1[] = "8080";
    char str2[] = "10abcd";
    char str3[] = "abc20";

    std::cout << atoi(str1) << std::endl;
    std::cout << atoi(str2) << std::endl;
    std::cout << atoi(str3) << std::endl;
    return 0;
}
