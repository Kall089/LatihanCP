#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    int n, target;
    cin >> n >> target;

    vector<int> coin(n);

    for (int i = 0; i < n; i++)
    {
        cin >> coin[i];
    }

    vector<int> dp(target + 1, INF);

    dp[0] = 0;

    for (int v = 1; v <= target; v++)
    {
        for (int c : coin)
        {
            if (v >= c && coin[v - c] != INF)
            {
                dp[v] = min(dp[v], dp[v - c] + 1);
            }
        }
    }

    cout << dp[target];
}