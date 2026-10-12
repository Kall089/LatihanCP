/*
============================================================
✅ Solution 1: Lompat Katak Dasar (Frog 1 - AtCoder DP-A)
============================================================
Approach: Dynamic Programming (Bottom-Up Tabulation & Top-Down Memoization)
Complexity: Time O(N) | Space O(N) (bisa O(1) dengan Rolling Array)

Key Insight:
Setiap kali berada di batu i, keputusan sebelumnya yang membawanya ke i
hanya bisa berasal dari batu (i - 1) atau batu (i - 2).
Karena kita mencari biaya minimum, kita ambil nilai terkecil dari kedua transisi tersebut:
dp[i] = min(dp[i - 1] + |h[i] - h[i - 1]|, dp[i - 2] + |h[i] - h[i - 2]|)

Base Case:
dp[0] = 0 (berdiri di batu awal tidak membutuhkan energi).
dp[1] = |h[1] - h[0]| (hanya ada satu lompatan dari batu 0).

Sample 1:
Input:
4
10 30 40 20
Output:
30

Sample 2:
Input:
2
10 10
Output:
0

Sample 3:
Input:
6
30 10 60 10 60 50
Output:
40
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    // Pendekatan Bottom-Up (Tabulasi)
    vector<int> dp(n, INF);
    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);

    for (int i = 2; i < n; i++) {
        dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]),
                    dp[i - 2] + abs(h[i] - h[i - 2]));
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
