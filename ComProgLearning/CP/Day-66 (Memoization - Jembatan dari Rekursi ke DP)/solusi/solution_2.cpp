/*
============================================================
✅ Solution 2: Kurir di Pematang Sawah (Frog Jump Min Energy)
============================================================
Approach: Top-Down Dynamic Programming with Memoization
Complexity: Time O(N) | Space O(N)
Key Insight:
1. Formulasi Rekursi Top-Down:
   f(i) menyatakan biaya minimum dari petak i menuju petak akhir n - 1.
   Kasus dasar: f(n - 1) = 0.
   Dari petak i, kurir dapat melangkah ke:
   - j = i + 1, dengan biaya |H[i] - H[i + 1]| + f(i + 1)
   - j = i + 2 (jika i + 2 < n), dengan biaya |H[i] - H[i + 2]| + f(i + 2)
   Maka: f(i) = min_{j \in {i+1, i+2}} (|H[i] - H[j]| + f(j)).

2. Memoisasi:
   Setiap submasalah f(i) dicatat dalam tabel `memo` dan ditandai oleh `seen`.
   Pemanggilan dari f(0) menjamin setiap indeks 0..n-1 hanya dihitung sekali.

3. Tipe Data:
   Ketinggian H[i] mencapai 10^9, sehingga selisih dan jumlah biaya membutuhkan `long long`.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<ll> memo(n, 0);
    vector<bool> seen(n, false);

    // Fungsi rekursif top-down mencari energi minimum dari petak i ke n - 1
    function<ll(int)> solve = [&](int i) -> ll {
        // Base case: sudah di petak akhir
        if (i == n - 1) return 0;

        // Cek memo
        if (seen[i]) return memo[i];
        seen[i] = true;

        ll best = INF;

        // Opsi 1: melangkah ke i + 1
        if (i + 1 < n) {
            best = min(best, llabs(h[i] - h[i + 1]) + solve(i + 1));
        }

        // Opsi 2: melangkah ke i + 2
        if (i + 2 < n) {
            best = min(best, llabs(h[i] - h[i + 2]) + solve(i + 2));
        }

        return memo[i] = best;
    };

    cout << solve(0) << "\n";

    return 0;
}
