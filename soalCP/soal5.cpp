#include <bits/stdc++.h>
using namespace std;

#define ll long long

void faktorisasi(ll N)
{

    vector<pair<ll, int>> hasil;

    for (int i = 2; i * i <= N; i++)
    {

        if (N % i == 0)
        {
            int a = 0;
            while (N % i == 0)
            {
                a++;
                N = N / i;
            }
            hasil.push_back({i, a});
        }
    }

    if (N != 1)
    {
        hasil.push_back({N, 1});
    }

    for (int i = 0; i < hasil.size(); i++)
    {
        cout << hasil[i].first;
        if (hasil[i].second > 1)
        {
            cout << "^" << hasil[i].second;
        }

        if (i + 1 < hasil.size())
        {
            cout << " x ";
        }
    }
}

int main()
{
    int N;
    cin >> N;
    faktorisasi(N);
}