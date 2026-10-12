/*
============================================================
✅ Solution 1: Penukaran Koin Minimum (Minimizing Coins)
============================================================
Approach: Dynamic Programming 1D (Bottom-Up Tabulation)
Complexity: Time O(N * X) | Space O(X)
Key Insight:
Setiap kali ingin membentuk nominal i, koin terakhir yang dipakai bisa berupa
sembarang koin c di mana c <= i. Kita mencari minimum di antara semua pilihan:
dp[i] = min_{c} (dp[i - c] + 1).

Base case:
dp[0] = 0 (membentuk nominal 0 butuh 0 koin).
dp[1...X] = INF (menandai nominal belum terjangkau).

Edge case & guard:
- Jika dp[i - c] == INF, transisi tidak boleh diambil agar tidak terjadi overflow.
- Kasus X = 0 langsung mencetak 0.
- Jika dp[X] tetap INF di akhir, cetak -1.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // Step 1: Inisialisasi tabel DP
    vector<int> dp(x + 1, INF);
    dp[0] = 0;

    // Step 2: Tabulasi Bottom-Up
    for (int i = 1; i <= x; i++) {
        for (int coin : c) {
            if (i >= coin && dp[i - coin] != INF) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // Step 3: Output jawaban
    if (dp[x] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }

    return 0;
}
