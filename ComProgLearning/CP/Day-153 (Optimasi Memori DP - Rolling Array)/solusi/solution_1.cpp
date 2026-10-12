/*
============================================================
✅ Solution 1: Arus Logistik Berkas Besar (Grid Min Path O(M) Space)
============================================================
Approach: 1D Dynamic Programming (Single Row In-Place Update)
Complexity: Time O(N * M) | Space O(M)
Key Insight:
1. Mengapa Cukup 1 Baris?
   Perhatikan transisi 2D standar:
   dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]).
   Untuk menghitung sel (i, j), kita hanya membutuhkan:
   - dp[i-1][j]: nilai tepat di atasnya.
   - dp[i][j-1]: nilai tepat di kirinya.

2. Invariant Pengisian 1D In-Place:
   Jika kita hanya memiliki satu array dp[0..M-1]:
   Saat kita berada pada iterasi kolom j:
   - dp[j] masih menyimpan nilai dari baris sebelumnya (i - 1, j).
   - dp[j-1] sudah diperbarui pada iterasi sebelumnya, sehingga menyimpan nilai (i, j - 1).
   Oleh karena itu:
   dp[j] = grid[i][j] + min(dp[j], dp[j-1]).
   Dengan demikian, nilai atas dan kiri dapat dibaca secara bersamaan tanpa tabel 2D!

3. Input Streaming:
   Nilai grid dibaca satu per satu dari `cin >> val` tanpa pernah disimpan ke dalam matriks 2D,
   sehingga pemakaian memori murni O(M) (~16 KB untuk M = 2000), jauh di bawah batas 64 MB.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<ll> dp(m, INF);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll val;
            cin >> val;

            if (i == 0 && j == 0) {
                // Sel awal (0, 0)
                dp[j] = val;
            } else {
                ll from_up = dp[j];                  // Nilai dari baris i - 1
                ll from_left = (j > 0 ? dp[j - 1] : INF); // Nilai dari kolom j - 1

                dp[j] = val + min(from_up, from_left);
            }
        }
    }

    cout << dp[m - 1] << "\n";

    return 0;
}
