/*
============================================================
✅ Solution 4: Pembagian Harta Warisan (0/1 Knapsack Top-Down)
============================================================
Approach: Top-Down Dynamic Programming with 2D Memoization
Complexity: Time O(N * W) | Space O(N * W)
Key Insight:
1. Rekursi Alami 0/1 Knapsack:
   solve(i, s) menyatakan kepuasan maksimum yang dapat diraih dari himpunan barang indeks i..N-1
   dengan sisa kapasitas ransel sebesar s.
   - Jika i == N atau s == 0, tidak ada barang lagi yang bisa diambil, nilai = 0.
   - Pilihan 1: Jangan ambil barang i -> solve(i + 1, s).
   - Pilihan 2: Ambil barang i (jika w[i] <= s) -> v[i] + solve(i + 1, s - w[i]).
   Hasil terbaik adalah maksimum dari kedua pilihan tersebut.

2. Memoisasi 2D:
   Array memo[N + 1][W + 1] diinisialisasi dengan -1.
   Karena semua nilai v[i] >= 0, nilai -1 berfungsi sempurna sebagai penanda belum dikunjungi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    // Tabel memo 2D diinisialisasi dengan -1
    vector<vector<ll>> memo(n + 1, vector<ll>(W + 1, -1));

    function<ll(int, int)> solve = [&](int i, int s) -> ll {
        // Base case: sudah memeriksa semua barang atau kapasitas habis
        if (i == n || s == 0) return 0;

        // Cek memo
        if (memo[i][s] != -1) return memo[i][s];

        // Opsi 1: Lewatkan barang ke-i
        ll res = solve(i + 1, s);

        // Opsi 2: Ambil barang ke-i jika kapasitas mencukupi
        if (w[i] <= s) {
            res = max(res, v[i] + solve(i + 1, s - w[i]));
        }

        return memo[i][s] = res;
    };

    cout << solve(0, W) << "\n";

    return 0;
}
