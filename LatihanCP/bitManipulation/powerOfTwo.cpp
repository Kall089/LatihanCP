#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    if ((n & (n - 1)) == 0)
    {
        cout << "Power of two";
    }
    else
    {
        cout << "Not a power of two";
    }
}