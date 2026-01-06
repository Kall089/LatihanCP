#include <iostream>

using namespace std;

void clearLastBit(int &n, int i)
{
    int mask = (-1 << i);
    n = n & mask;
}

int main()
{
    int n = 15;
    int i;
    cin >> i;

    clearLastBit(n, i);
    cout << n;
}