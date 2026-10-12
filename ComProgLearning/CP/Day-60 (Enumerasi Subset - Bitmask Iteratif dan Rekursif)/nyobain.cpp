#include <bits/stdc++.h>
using namespace std;

int getIthBit(int n, int i)
{
    int mask = (1 << i);
    return (n & mask) > 0 ? 1 : 0;
}

void setIthBit(int &n, int i)
{
    int mask = (1 << i);
    n = (n | mask);
}

void clearIthBit(int &n, int i)
{
    int mask = ~(1 << i);
    n = n & mask;
}

void updateIthBit(int &n, int i, int v)
{
    clearIthBit(n, i);
    int mask = (v << i);
    n = n | mask;
}

int main()
{
    int n = 5;
    int i;
    cin >> i;

    setIthBit(n, i);
    cout << n;
}