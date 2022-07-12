#include <cstring>
#include <iostream>
using namespace std;

// Driver Code
int main()
{
    char str[] = "helloworld";
    memset(str, 0, sizeof(str));
    cout << str << endl;
    return 0;
}
