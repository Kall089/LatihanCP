/*
============================================================
📋 TUGAS 09: Partisi dengan Pembatasan Kapasitas Maksimum Segmen
============================================================
Source: Classic D&C DP Optimization
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Segment Max Constraints

PROBLEM:
Diberikan N paket barang berurutan dengan bobot a[0], ..., a[N-1].
Bagi paket menjadi TEPAT K segmen tak kosong.
Namun, satu segmen TIDAK BOLEH MEMILIKI PANJANG LEBIH DARI R PAKET (r - l + 1 <= R).
Biaya segmen adalah kuadrat dari total bobotnya.

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh paket! Jika mustahil, cetak -1.

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan R.
Baris kedua berisi N bilangan bulat non-negatif a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 20.000
1 <= K <= min(N, 30)
1 <= R <= N
0 <= a[i] <= 1.000.000

SAMPLE INPUT 1:
4 2 2
1 2 3 4

SAMPLE OUTPUT 1:
58
(Setiap segmen maksimal panjang 2. Bagi [1, 2] dan [3, 4] -> sum 3^2 + 7^2 = 9 + 49 = 58)

SAMPLE INPUT 2:
4 2 1
1 2 3 4

SAMPLE OUTPUT 2:
-1
(K * R = 2 * 1 = 2 < 4, mustahil mengcover seluruh 4 paket)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, r_cap;
    if (!(cin >> n >> k >> r_cap)) return 0;

    // TODO: Selesaikan dengan D&C DP dengan pembatas j >= mid - r_cap

    return 0;
}
