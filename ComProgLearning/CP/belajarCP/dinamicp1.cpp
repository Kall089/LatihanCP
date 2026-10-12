#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, W;
    cin >> n >> W;

    vector<int> berat(n), nilai(n);

    for (int i = 1; i <= n; i++)
    {
        cin >> berat[i] >> nilai[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            dp[i][w] = dp[i - 1][w];
            if (w >= berat[i])
            {
                dp[i][w] = max(dp[i][w], dp[i - 1][w - berat[i]] + nilai[i]);
            }
        }
    }

    cout << dp[n][W];
}