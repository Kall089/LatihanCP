#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> dp(n, 0);
    dp[0] = 0;
    dp[1] = abs(a[1] - a[0]);

    for (int i = 2; i < n; i++)
    {
        int hitung1 = dp[i - 1] + abs(a[i] - dp[i - 1]);
        int hitung2 = dp[i - 1] + abs(a[i] - dp[i - 2]);

        dp[i] = min(hitung1, hitung2);
    }

    cout << dp[n - 1];
}