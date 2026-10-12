/*
============================================================
✅ Solution 3: Denah Festival Batik (Grid Paths with Obstacles Top-Down)
============================================================
Approach: 2D Top-Down Dynamic Programming with Memoization
Complexity: Time O(N * M) | Space O(N * M)
Key Insight:
1. Rekursi Sufiks dari Sel (r, c) ke (N-1, M-1):
   solve(r, c) menghitung banyak cara mencapai pojok kanan-bawah dari posisi saat ini (r, c).
   - Jika r >= N atau c >= M: di luar peta, cara = 0.
   - Jika grid[r][c] == '#': sel terhalang, cara = 0.
   - Jika r == N - 1 dan c == M - 1: sel tujuan, cara = 1.
   - Selain itu: pengunjung dapat melangkah ke bawah (r + 1, c) atau ke kanan (r, c + 1).
     solve(r, c) = (solve(r + 1, c) + solve(r, c + 1)) % MOD.

2. Memoisasi 2D:
   Matriks memo[N][M] dan seen[N][M] menyimpan hasil perhitungan setiap sel.
   Karena setiap sel (r, c) dikunjungi dan dihitung tepat satu kali, waktu eksekusi
   dibatasi oleh banyak sel yaitu O(N * M).

3. Penanganan Sel Awal/Akhir:
   Jika sel awal (0, 0) berupa '#', fungsi langsung mengembalikan 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<ll>> memo(n, vector<ll>(m, 0));
    vector<vector<bool>> seen(n, vector<bool>(m, false));

    // Fungsi rekursif 2D top-down
    function<ll(int, int)> solve = [&](int r, int c) -> ll {
        // Base case 1: di luar batas grid
        if (r >= n || c >= m) return 0;

        // Base case 2: sel tertutup / rintangan
        if (grid[r][c] == '#') return 0;

        // Base case 3: mencapai sel tujuan
        if (r == n - 1 && c == m - 1) return 1;

        // Cek memo
        if (seen[r][c]) return memo[r][c];
        seen[r][c] = true;

        // Transisi: melangkah ke bawah dan ke kanan
        ll ways = (solve(r + 1, c) + solve(r, c + 1)) % MOD;
        return memo[r][c] = ways;
    };

    cout << solve(0, 0) << "\n";

    return 0;
}
