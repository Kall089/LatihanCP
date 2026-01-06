#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;

    if (x & 1)
    {
        cout << "Odd" << endl;
        cout << (x << 1);
    }
    else
    {
        cout << "Even";
    }
}