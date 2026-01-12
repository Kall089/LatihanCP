#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100000

int sieveArr[N + 1] = {0};
vector<int> primes;

void sieve()
{
    for (ll i = 2; i <= N; i++)
    {
        if (sieveArr[i] == 0)
        {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i)
            {
                sieveArr[j] = 1;
            }
        }
    }
}

int main()
{
    sieve();
    int t;
    cin >> t;

    while (t--)
    {
        int m, n;
        cin >> m >> n;
        vector<int> segment(n - m + 1, 0);

        for (auto p : primes)
        {
            if (p * p > n)
            {
                break;
            }

            int start = (m / p) * p;

            if (p >= m and p <= n)
            {
                start = 2 * p;
            }

            for (int j = start; j <= n; j = j + p)
            {
                if (j < m)
                {
                    continue;
                }
                segment[j - m] = 1;
            }
        }
        for (int i = m; i <= n; i++)
        {
            if (segment[i - m] == 0)
            {
                cout << i << endl;
            }
        }
        cout << endl;
    }
}