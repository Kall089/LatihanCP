#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll fpb(int a, int b)
{

    if (a == 0)
    {
        return b;
    }
    else if (b == 0)
    {
        return a;
    }
    else
    {
        return fpb(b, a % b);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    ll n_awal = n;
    ll m_awal = m;

    ll hasil_fpb = fpb(n, m);

    n = n / hasil_fpb;
    m = m / hasil_fpb;

    ll hasil = ((n_awal + n) * (m_awal + m)) - (n_awal * m_awal);

    cout << hasil;
}