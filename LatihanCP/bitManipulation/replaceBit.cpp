#include <iostream>

using namespace std;

void clearBitsInRange(int &n, int i, int j)
{
    int a = (~0) << (j + 1);
    int b = (1 << i) - 1;
    int mask = a | b;
    n = n & mask;
}

void replaceBit(int &n, int i, int j, int m)
{
    clearBitsInRange(n, i, j);

    int mask = (m << i);
    n = n | mask;
}

int main()
{
    int n = 21;
    int i = 2;
    int j = 5;
    int m = 3;

    replaceBit(n, i, j, m);
    cout << n << endl;
}