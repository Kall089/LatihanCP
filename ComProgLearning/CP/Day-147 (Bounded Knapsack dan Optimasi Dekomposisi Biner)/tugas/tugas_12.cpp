/*
============================================================
📋 TUGAS 12: Bounded Knapsack dengan Kapasitas Berjarak
============================================================
Source: Educational / Range Capacity
Difficulty: Hard
Topics: Bounded Knapsack Range Capacity [L, R]

PROBLEM:
Sebuah lift pengangkut barang memiliki batasan keamanan operasional:
lift HANYA boleh berjalan jika total bobot muatan berada dalam rentang [L, R]
(yaitu L <= Total Bobot <= R).
Jika total bobot < L, lift mendeteksi muatan kurang seimbang.
Jika total bobot > R, lift kelebihan beban (overload).

Tersedia N jenis paket muatan. Paket jenis ke-i berbobot w[i], bernilai manfaat v[i],
dan tersedia sebanyak c[i] buah.
Tentukan total manfaat maksimum yang dapat dibawa oleh lift dalam satu kali jalan
yang memenuhi batas beban aman [L, R].
Jika tidak ada kombinasi paket yang menghasilkan bobot dalam rentang [L, R], cetak -1.

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, L, dan R.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: manfaat maksimum dalam rentang bobot aman [L, R], atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 80
1 <= L <= R <= 20.000
1 <= w[i] <= R
1 <= v[i] <= 10^9
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
2 7 9
3 5 2
4 8 2

SAMPLE OUTPUT 1:
18
(Penjelasan: Ambil 1 paket jenis 0 (bobot 3, nilai 5) + 1 paket jenis 1 (bobot 4, nilai 8) = bobot 7, nilai 13.
Atau ambil 2 paket jenis 1 (bobot 8, nilai 16) = bobot 8, nilai 16.
Atau ambil 1 paket 1 (4, 8) + 2 paket 0 (6, 10) = bobot 10 > 9 (overload).
Tunggu: 2 paket 0 (bobot 6) -> < 7.
Apakah ada kombinasi lain?
1 paket 0 (3, 5) + 1 paket 1 (4, 8) = bobot 7 in [7, 9], nilai 13.
2 paket 1 (8, 16) = bobot 8 in [7, 9], nilai 16.
Maksimum = 16!)

SAMPLE INPUT 2:
1 10 12
3 10 2

SAMPLE OUTPUT 2:
-1
(Penjelasan: Maksimal bobot hanya 3*2 = 6 < 10, mustahil)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, L, R;
    if (!(cin >> n >> L >> R)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack dengan Exact Reachability [L, R]
    // vector<ll> dp(R + 1, -1); dp[0] = 0;
    // Update mundur dengan paket biner
    // max_val = max_{L <= j <= R} dp[j]

    return 0;
}
