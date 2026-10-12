/*
============================================================
✅ Solution 6: Penukaran Mata Uang Minimum & Banyak Cara (Coin Change Synthesis)
============================================================
Approach: 1D Dynamic Programming (Unbounded Optimization + Unbounded Counting)
Complexity: Time O(N * X) | Space O(X)
Key Insight:
1. Dua Objektif dalam Satu Masalah:
   - min_coins[s]: koin paling sedikit untuk jumlah s.
     Basis: min_coins[0] = 0, lainnya INF.
     Transisi: min_coins[s] = min(min_coins[s], min_coins[s - c] + 1).
   - ways[s]: banyak kombinasi koin berbeda (unordered) untuk jumlah s.
     Basis: ways[0] = 1, lainnya 0.
     Transisi: ways[s] = (ways[s] + ways[s - c]) % MOD.

2. Urutan Loop Kombinasi (Bukan Permutasi):
   Agar 1+2 tidak dianggap berbeda dengan 2+1, loop KOIN HARUS BERADA DI LUAR,
   dan loop nominal s maju dari c ke X di dalam.
   Kedua array DP dapat di-update secara simultan dalam satu pasang perulangan!

3. Kasus Khusus X = 0:
   Nominal 0 membutuhkan 0 koin dan memiliki 1 cara (himpunan kosong).
   Jika min_coins[X] == INF, berarti nominal X tidak mungkin dibentuk, cetak "-1 0".
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    vector<int> min_coins(x + 1, INF);
    vector<int> ways(x + 1, 0);

    min_coins[0] = 0;
    ways[0] = 1;

    for (int c : coins) {
        for (int s = c; s <= x; s++) {
            if (min_coins[s - c] != INF) {
                min_coins[s] = min(min_coins[s], min_coins[s - c] + 1);
            }
            ways[s] = (ways[s] + ways[s - c]) % MOD;
        }
    }

    if (min_coins[x] == INF) {
        cout << "-1 0\n";
    } else {
        cout << min_coins[x] << " " << ways[x] << "\n";
    }

    return 0;
}
