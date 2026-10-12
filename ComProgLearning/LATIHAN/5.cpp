#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);
    vector<int> c(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<vector<int>> dp(3, vector<int>(n, 0));
    dp[0][0] = a[0];
    dp[1][0] = b[0];
    dp[2][0] = c[0];

    int hasil_max = 0;

    for (int i = 1; i < n; i++)
    {
        dp[0][i] = a[i] + max(dp[1][i - 1], dp[2][i - 1]);
        dp[1][i] = b[i] + max(dp[0][i - 1], dp[2][i - 1]);
        dp[2][i] = c[i] + max(dp[0][i - 1], dp[1][i - 1]);

        hasil_max = max({dp[0][n - 1], dp[1][n - 1], dp[2][n - 1]});
    }

    cout << hasil_max;
}