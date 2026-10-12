/*
============================================================
✅ Solution 1: Agenda Stan dan Anggaran (House Robber + Knapsack)
============================================================
Approach: Dynamic Programming (House Robber + 0/1 Knapsack Hybrid)
Complexity: Time O(N * W) | Space O(W) atau O(N * W)
Key Insight:
1. Sintesis Masalah:
   - Dari House Robber: kita tidak boleh memilih dua elemen bertetangga (i dan i - 1).
   - Dari Knapsack: total bobot elemen terpilih tidak boleh melebihi kapasitas W.

2. Formulasi State:
   dp[i][s] = kepuasan maksimum yang bisa diraih dari stan 1..i dengan batas biaya s.
   Pilihan pada stan ke-i:
   - Skip stan i: nilai terbaik sama dengan dp[i - 1][s].
   - Take stan i: biaya bertambah w[i] dan kepuasan bertambah v[i].
     Karena stan i - 1 dilarang diambil, kita harus melompat ke dp[i - 2][s - w[i]]!
   Rumus:
   dp[i][s] = max(dp[i - 1][s], dp[i - 2][s - w[i]] + v[i]) (jika s >= w[i]).

3. Optimasi Ruang:
   Karena dp[i] hanya butuh dp[i - 1] dan dp[i - 2], kita bisa menggunakan 3 buffer:
   older (mewakili i - 2), prev (mewakili i - 1), dan cur (mewakili i).
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

    // older = baris i - 2, prev = baris i - 1, cur = baris i
    vector<ll> older(W + 1, 0);
    vector<ll> prev(W + 1, 0);
    vector<ll> cur(W + 1, 0);

    for (int i = 0; i < n; i++) {
        int w;
        ll v;
        cin >> w >> v;

        for (int s = 0; s <= W; s++) {
            // Opsi 1: Lewatkan stan i
            cur[s] = prev[s];

            // Opsi 2: Ambil stan i (hanya boleh menggabungkan dengan older = i - 2)
            if (s >= w) {
                cur[s] = max(cur[s], older[s - w] + v);
            }
        }

        // Geser jendela state
        older.swap(prev);
        prev.swap(cur);
    }

    cout << prev[W] << "\n";

    return 0;
}
