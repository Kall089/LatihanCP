/*
============================================================
📋 TUGAS 15: Optimasi Peluru Pertahanan (Bounded Strategic)
============================================================
Source: Competitive Programming Variation
Difficulty: Hard
Topics: Bounded Knapsack Strategy, Multi-Cost Resource

PROBLEM:
Sebuah benteng pertahanan memiliki kapasitas gudang amunisi seberat W kg.
Terdapat N jenis proyektil meriam.
Proyektil jenis ke-i memiliki berat w[i] kg, menghasilkan daya hancur v[i] poin,
dan persediaan stok di markas militer hanya ada c[i] buah proyektil jenis tersebut.
Sebagai komandan benteng, kamu harus mengisi gudang amunisi dengan kombinasi proyektil
sedemikian rupa sehingga total bobot tidak melampaui kapasitas W kg,
namun total daya hancur yang dihasilkan adalah SEBESAR MUNGKIN.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: total daya hancur maksimum.

CONSTRAINTS:
1 <= N <= 250
1 <= W <= 50.000
1 <= w[i] <= W
1 <= v[i] <= 10^9
1 <= c[i] <= 10.000

SAMPLE INPUT 1:
3 30
8 25 3
6 18 4
10 32 2

SAMPLE OUTPUT 1:
96
(Penjelasan: Ambil 2 proyektil 2 (bobot 20, daya 64) + 1 proyektil 0 (bobot 8, daya 25) = bobot 28, daya 89.
Atau 1 proyektil 0 (8, 25) + 3 proyektil 1 (18, 54) = bobot 26, daya 79.
Atau 3 proyektil 0 (24, 75) + 1 proyektil 1 (6, 18) = bobot 30, daya 93.
Atau 1 proyektil 2 (10, 32) + 2 proyektil 0 (16, 50) = bobot 26, daya 82.
Atau 1 proyektil 2 (10, 32) + 1 proyektil 0 (8, 25) + 2 proyektil 1 (12, 36) = bobot 30, daya 32 + 25 + 36 = 93.
Atau 5 proyektil 1 (jika ada) -> stok hanya 4 (bobot 24, daya 72).
Jika ambil 2 proyektil 0 (16, 50) + 2 proyektil 1 (12, 36) = bobot 28, daya 86.
Jika ambil 3 proyektil 0 (24, 75) + 1 proyektil 1 (6, 18) = bobot 30, daya 93.
Cek jika ada: 2 proyektil 2 (20, 64) + 1 proyektil 1 (6, 18) = bobot 26, daya 82.
Pilihan terbaik: 93!)
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
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack dengan Dekomposisi Biner + Hybrid Shortcut
    // vector<ll> dp(W + 1, 0)
    // Jika c[i] * w[i] >= W -> Unbounded forward loop
    // Jika tidak -> Bounded binary backward loop

    return 0;
}
