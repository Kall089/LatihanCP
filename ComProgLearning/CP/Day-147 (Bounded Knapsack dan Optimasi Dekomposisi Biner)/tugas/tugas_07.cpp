/*
============================================================
📋 TUGAS 07: Penjualan Emas Batangan (Bounded DP Nilai Besar)
============================================================
Source: Classic DP / Knapsack Dual
Difficulty: Hard
Topics: Bounded Knapsack DP on Values (W Besar)

PROBLEM:
Seorang kolektor ingin membawa batangan emas dengan total nilai MINIMAL V.
Terdapat N jenis ukuran batangan emas. Batangan ke-i berbobot w[i] gram,
bernilai v[i] dolar, dan tersedia sebanyak c[i] batang.
Kolektor ingin meminimalkan total bobot batangan emas yang harus ia pikul
untuk mencapai total nilai sedikitnya V.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan V.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: bobot minimum untuk mencapai nilai >= V, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 50
1 <= V <= 5.000
1 <= w[i] <= 10^6
1 <= v[i] <= 100
1 <= c[i] <= 100

SAMPLE INPUT 1:
2 10
20 3 2
30 4 2

SAMPLE OUTPUT 1:
70
(Penjelasan: Ambil dua batang jenis 0 (nilai 6, bobot 40) + satu batang jenis 1 (nilai 4, bobot 30) = total nilai 10, bobot 70)

SAMPLE INPUT 2:
1 100
50 5 10

SAMPLE OUTPUT 2:
-1
(Penjelasan: Maksimal nilai yang ada hanya 5 * 10 = 50 < 100, mustahil)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, V;
    if (!(cin >> n >> V)) return 0;

    vector<ll> w(n);
    vector<int> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack dengan DP pada State Nilai
    // dp[val] = bobot minimum untuk mencapai total nilai val
    // Pecah c[i] secara biner q
    // dp[val] = min(dp[val], dp[val - q * v[i]] + q * w[i])

    return 0;
}
