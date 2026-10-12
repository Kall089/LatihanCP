/*
============================================================
✅ Solution 6: Lampu Taman Sejumlah K
============================================================
Approach: Dynamic Programming 3D (State Counting Multi-Dimensi)
Complexity: Time O(N * K) | Space O(N * K) atau O(K) dengan Rolling Array

Key Insight:
Untuk menentukan keabsahan menyalakan lampu ke-i, kita hanya perlu tahu
apakah lampu ke-(i - 1) menyala atau padam.
Selain itu, kita perlu melacak berapa total lampu yang sudah dinyalakan sejauh ini.

Definisi State:
dp[i][j][0] = banyak konfigurasi memilih j lampu dari i tiang pertama dengan tiang ke-i PADAM.
dp[i][j][1] = banyak konfigurasi memilih j lampu dari i tiang pertama dengan tiang ke-i MENYALA.

Transisi:
1. Tiang ke-i padam:
   dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD
2. Tiang ke-i menyala:
   dp[i][j][1] = (j >= 1 ? dp[i - 1][j - 1][0] : 0)

Basis:
dp[0][0][0] = 1 (0 tiang, 0 lampu, tiang fiktif 0 dianggap padam)
Semua state lainnya bernilai 0.

Jawaban akhir untuk N tiang dan K lampu:
(dp[N][K][0] + dp[N][K][1]) % MOD

Sample 1:
Input:
5 2
Output:
6

Sample 2:
Input:
3 2
Output:
1

Sample 3:
Input:
0 0
Output:
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    if (k > (n + 1) / 2) {
        cout << 0 << "\n";
        return 0;
    }

    if (n == 0 && k == 0) {
        cout << 1 << "\n";
        return 0;
    }

    // dp[i][j][0/1]
    vector<vector<array<long long, 2>>> dp(n + 1, vector<array<long long, 2>>(k + 1, {0, 0}));
    dp[0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // Tiang i PADAM
            dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;

            // Tiang i MENYALA
            if (j >= 1) {
                dp[i][j][1] = dp[i - 1][j - 1][0] % MOD;
            }
        }
    }

    long long ans = (dp[n][k][0] + dp[n][k][1]) % MOD;
    cout << ans << "\n";

    return 0;
}
