#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // 1 & 2: Gunakan long long dan ukuran n+1
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    // Kasus khusus kalau rumahnya cuma 1
    if (n == 1)
    {
        cout << a[1] << "\n";
        return 0;
    }

    vector<long long> dp(n + 1, 0);

    // 4: Base case untuk rumah 1 dan rumah 2
    dp[1] = a[1];
    dp[2] = max(a[1], a[2]);

    // 3: Loop dimulai dari 3, menggunakan rumus yang benar
    for (int i = 3; i <= n; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + a[i]);
    }

    cout << dp[n] << "\n";
    return 0;
}