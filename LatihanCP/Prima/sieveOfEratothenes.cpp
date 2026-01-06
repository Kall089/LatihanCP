#include <iostream>
#define ll long long
#define vll vector<long long>
#define rep(i, a, b) for (int i = a; i < b; i++)

using namespace std;

void sieveOfEratothenes(vll &isPrime, int n)
{
    rep(i, 2, n + 1)
    {
        isPrime[i] = true;
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vll isPrime(n);
    sieveOfEratothenes(isPrime, n);

    for (int i = 2; i < n; i++)
    {
        if (isPrime[i])
        {
            cout << i << " ";
        }
    }
}