/*
============================================================
✅ Solution 5: Penjelajah Labirin Grid Berbobot (Grid Min Path Reconstruction)
============================================================
Approach: 2D Suffix DP + Lexicographical Greedy Forward Reconstruction
Complexity: Time O(R * C) | Space O(R * C)
Key Insight:
1. Mengapa Suffix DP?
   Kita diminta string langkah leksikografis terkecil dari start (0, 0) ke finish (R-1, C-1)
   dengan aturan 'D' < 'R'. Langkah pertama di (0, 0) sangat menentukan leksikografi!
   Dengan Suffix DP:
   dp[r][c] = biaya minimum dari sel (r, c) hingga sel tujuan (R - 1, C - 1).
   Basis: dp[R - 1][C - 1] = grid[R - 1][C - 1].
   Untuk r dari R-1 turun ke 0, c dari C-1 turun ke 0:
     next_cost = min(dp[r + 1][c] (jika r + 1 < R), dp[r][c + 1] (jika c + 1 < C))
     dp[r][c] = grid[r][c] + next_cost.

2. Rekonstruksi Maju dari (0, 0):
   Mulai dari r = 0, c = 0.
   Pada setiap langkah:
   - Evaluasi opsi 'D' terlebih dahulu:
     Jika r + 1 < R dan dp[r][c] == grid[r][c] + dp[r + 1][c]:
       PILIH 'D' karena 'D' < 'R'!
       r++;
   - Jika opsi 'D' tidak optimal, maka PASTI opsi 'R' yang optimal:
     PILIH 'R';
     c++;
   Ulangi sampai mencapai (R - 1, C - 1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<vector<ll>> grid(R, vector<ll>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
        }
    }

    // dp[r][c]: biaya minimum dari (r, c) ke (R-1, C-1)
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[R - 1][C - 1] = grid[R - 1][C - 1];

    for (int r = R - 1; r >= 0; r--) {
        for (int c = C - 1; c >= 0; c--) {
            if (r == R - 1 && c == C - 1) continue;

            ll next_cost = INF;
            if (r + 1 < R) next_cost = min(next_cost, dp[r + 1][c]);
            if (c + 1 < C) next_cost = min(next_cost, dp[r][c + 1]);

            dp[r][c] = grid[r][c] + next_cost;
        }
    }

    cout << dp[0][0] << "\n";

    // Rekonstruksi langkah leksikografis terkecil ('D' < 'R')
    string path = "";
    int cur_r = 0, cur_c = 0;
    while (cur_r < R - 1 || cur_c < C - 1) {
        // Cek opsi 'D' dulu
        if (cur_r + 1 < R && dp[cur_r][cur_c] == grid[cur_r][cur_c] + dp[cur_r + 1][cur_c]) {
            path.push_back('D');
            cur_r++;
        } else {
            path.push_back('R');
            cur_c++;
        }
    }

    cout << path << "\n";

    return 0;
}
