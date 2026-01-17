#include <bits/stdc++.h>
using namespace std;

void isPrime(int N)
{
    int count = 0;
    for (int i = 2; i < N; i++)
    {
        if (N % i == 0)
        {
            count++;
        }
    }
    if (count <= 2)
    {
        cout << "YA" << "\n";
    }
    else
    {
        cout << "BUKAN" << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, T;
    cin >> T;

    while (T--)
    {
        cin >> N;
        isPrime(N);
    }
}