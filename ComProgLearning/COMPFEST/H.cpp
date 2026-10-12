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

    int n;
    cin >> n;

    vector<long long> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (i >= 1)
        {
            dp[i] = (dp[i - 1] + dp[i]);
        }

        if (i >= 2)
        {
            dp[i] = (dp[i - 2] + dp[i]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        ll hasil = 0;
        ll c = 0;
        ll L, R, K;
        cin >> L >> R >> K;

        for (int j = L; j <= R; j++)
        {
            for (int k = L; k <= R; k++)
            {
                if (k % j == 0)
                {
                    hasil = max(hasil, fpb(dp[j], dp[k]));
                }
            }
        }
        cout << hasil;
    }
}