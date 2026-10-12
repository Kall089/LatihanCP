#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> triangle(n);

    for (int i = 0; i < n; i++)
    {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; j++)
        {
            cin >> triangle[i][j];
        }
    }

    vector<int> dp = triangle[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[j] = triangle[i][j] + min(dp[j + 1], dp[j]);
        }
    }

    cout << dp[0];
}