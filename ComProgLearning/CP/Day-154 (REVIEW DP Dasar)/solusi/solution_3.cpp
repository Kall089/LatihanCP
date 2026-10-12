/*
============================================================
✅ Solution 3: Rute Hadiah dan Banyak Pemenang (Grid Max + Way Counting)
============================================================
Approach: 2D Dynamic Programming (Optimization + Counting DP)
Complexity: Time O(N * M) | Space O(N * M)
Key Insight:
1. Kombinasi Nilai Ekstrem dan Counting:
   Setiap sel (i, j) membutuhkan dua informasi:
   - best[i][j]: perolehan hadiah maksimum yang mungkin untuk mencapai (i, j).
   - ways[i][j]: banyak jalur unik yang menghasilkan perolehan hadiah tepat sama dengan best[i][j].

2. Logika Pembaruan State Berpasangan:
   Saat mempertimbangkan jalur dari atas (i - 1, j) atau kiri (i, j - 1):
   ll cand = best[prev_r][prev_c] + hadiah[i][j];
   - Jika cand > best[i][j]:
     Ditemukan jalur yang lebih menguntungkan!
     best[i][j] = cand;
     ways[i][j] = ways[prev_r][prev_c];
   - Jika cand == best[i][j]:
     Ada jalur alternatif dengan total nilai yang sama persis (seri):
     ways[i][j] = (ways[i][j] + ways[prev_r][prev_c]) % MOD;
   - Jika cand < best[i][j]:
     Jalur ini sub-optimal, abaikan sepenuhnya.

3. Kasus Khusus:
   - Nilai hadiah bisa bernilai sangat negatif, sehingga basis reachable diinisialisasi
     dengan -INF (misal -4e18).
   - Jika best[N-1][M-1] == -INF, cetak "IMPOSSIBLE".
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<ll>> best(n, vector<ll>(m, -INF));
    vector<vector<ll>> ways(n, vector<ll>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            string token;
            cin >> token;

            if (token == "#") {
                // Sel tertutup / dinding
                continue;
            }

            ll val = stoll(token);

            if (i == 0 && j == 0) {
                // Sel awal (0, 0)
                best[i][j] = val;
                ways[i][j] = 1;
                continue;
            }

            // Coba datang dari sel atas (i - 1, j) dan sel kiri (i, j - 1)
            int dr[] = {-1, 0};
            int dc[] = {0, -1};

            for (int d = 0; d < 2; d++) {
                int pr = i + dr[d];
                int pc = j + dc[d];

                if (pr >= 0 && pc >= 0 && best[pr][pc] != -INF) {
                    ll cand = best[pr][pc] + val;

                    if (cand > best[i][j]) {
                        best[i][j] = cand;
                        ways[i][j] = ways[pr][pc];
                    } else if (cand == best[i][j]) {
                        ways[i][j] = (ways[i][j] + ways[pr][pc]) % MOD;
                    }
                }
            }
        }
    }

    if (best[n - 1][m - 1] == -INF) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << best[n - 1][m - 1] << " " << ways[n - 1][m - 1] << "\n";
    }

    return 0;
}
