/*
============================================================
  Solution 6: Shortest Hamiltonian Path (Bitmask DP)
============================================================
Pendekatan: Bitmask DP klasik.
  State: dp[mask][v] = jarak minimum untuk mengunjungi semua kota
         dalam mask, dimulai dari kota 0, berakhir di kota v.
  Base: dp[1][0] = 0 (hanya kota 0, cost 0)
  Transisi: dp[mask|(1<<u)][u] = min(dp[mask|(1<<u)][u], dp[mask][v] + dist[v][u])
  Jawaban: min(dp[(1<<n)-1][v]) untuk v = 0..n-1

Kompleksitas Waktu: O(n² × 2^n)
Kompleksitas Memori: O(n × 2^n)

Alternatif: untuk n lebih besar, bisa menggunakan iterative deepening
atau optimasi memori dengan rolling mask.
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    // dp[mask][v]
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    // Base case: mulai dari kota 0
    dp[1][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] == INF) continue;
            if (!((mask >> v) & 1)) continue;

            // Coba pergi ke kota u yang belum dikunjungi
            for (int u = 0; u < n; u++) {
                if ((mask >> u) & 1) continue;
                if (dist[v][u] == INF) continue;
                int newMask = mask | (1 << u);
                dp[newMask][u] = min(dp[newMask][u], dp[mask][v] + dist[v][u]);
            }
        }
    }

    int allVisited = (1 << n) - 1;
    int ans = INF;
    for (int v = 0; v < n; v++) {
        ans = min(ans, dp[allVisited][v]);
    }

    cout << (ans == INF ? -1 : ans) << "\n";
    return 0;
}
