#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    vector<long long> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        dp[i] = max((long long)i, dp[i / 4] + dp[i / 3] + dp[i / 2]);
    }
    cout << dp[n];
}