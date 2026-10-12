/*
============================================================
✅ Solution 2: Lompat Katak dengan K Langkah (Frog 2 - AtCoder DP-B)
============================================================
Approach: Dynamic Programming Bottom-Up dengan Transisi Dinamis K
Complexity: Time O(N * K) | Space O(N)

Key Insight:
Pada batu ke-i, katak bisa datang dari batu mana pun di antara
(i - K) hingga (i - 1), asalkan indeks batu tersebut >= 0.
Kita mengevaluasi semua kemungkinan lompatan j (1 <= j <= K):
dp[i] = min_{1 <= j <= K, i - j >= 0} (dp[i - j] + |h[i] - h[i - j]|)

Dengan N = 100.000 dan K = 100:
Jumlah operasi maksimum = 10^5 * 100 = 10^7 operasi, sangat aman (< 0.1 detik).

Sample 1:
Input:
5 3
10 30 40 50 20
Output:
30

Sample 2:
Input:
3 1
10 20 10
Output:
20

Sample 3:
Input:
2 100
10 10
Output:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> dp(n, INF);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k && i - j >= 0; j++) {
            dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
        }
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
