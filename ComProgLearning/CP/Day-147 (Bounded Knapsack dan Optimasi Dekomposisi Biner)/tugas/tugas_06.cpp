/*
============================================================
📋 TUGAS 06: Rekonstruksi Pembelian Barang Bounded
============================================================
Source: Competitive Programming Classic
Difficulty: Hard
Topics: Bounded Knapsack Reconstruction, Backtracking

PROBLEM:
Diberikan N jenis barang dan ransel berkapasitas bobot W.
Barang ke-i berbobot w[i], bernilai v[i], dan persediaannya c[i] buah.
Tentukan nilai keuntungan total maksimum di baris pertama.
Di baris kedua, cetak kuantitas setiap barang yang diambil k[0], k[1], ..., k[N-1]
sedemikian sehingga 0 <= k[i] <= c[i] dan total bobot <= W.
Jika ada beberapa kombinasi dengan nilai maksimum yang sama, cetak salah satu.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Baris pertama: nilai keuntungan maksimum.
Baris kedua: N bilangan bulat dipisahkan spasi menyatakan kuantitas k[i].

CONSTRAINTS:
1 <= N <= 40
1 <= W <= 5.000
1 <= w[i] <= W
1 <= v[i] <= 10^9
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
2 10
3 7 2
4 10 2

SAMPLE OUTPUT 1:
24
0 2
(Penjelasan: Ambil 0 unit barang 0 dan 2 unit barang 1 (bobot 8, nilai 20).
Atau ambil 2 unit barang 0 (bobot 6, nilai 14) + 1 unit barang 1 (bobot 4, nilai 10) = bobot 10, nilai 24!
Kuantitas: 2 1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Package {
    int item_idx;
    int weight;
    ll value;
    int count;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Rekonstruksi Solusi Bounded Knapsack
    // 1. Bentuk paket-paket biner
    // 2. Tabulasi 2D DP dp[pkg_idx][w]
    // 3. Backtracking dari kapasitas optimal W
    // 4. Akumulasikan unit barang dan cetak

    return 0;
}
