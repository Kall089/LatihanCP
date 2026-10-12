#include <bits/stdc++.h>
using namespace std;

int main()
{

    string s;
    cin >> s;

    int n;
    cin >> n;

    vector<int> dp(s.length() + 1, 0);

    for (int i = 2; i <= s.length(); i++)
    {
        if (s[i - 2] == s[i - 1])
        {
            dp[i] = dp[i - 1] + 1;
        }
        else
        {
            dp[i] = dp[i - 1];
        }
    }

    while (n--)
    {
        int l, r;
        cin >> l >> r;

        cout << dp[r] - dp[l] << endl;
    }
}