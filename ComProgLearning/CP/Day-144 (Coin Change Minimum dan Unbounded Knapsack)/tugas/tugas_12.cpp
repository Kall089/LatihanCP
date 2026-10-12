/*
============================================================
📋 TUGAS 12: Nilai Maksimum dengan Kapasitas Tepat
============================================================
Source: Classic DP / Exact Knapsack
Difficulty: Hard
Topics: Exact Target Unbounded Knapsack

PROBLEM:
Diberikan N jenis barang. Barang ke-i memiliki bobot w[i] dan nilai v[i].
Setiap jenis barang boleh diambil berkali-kali tanpa batas.
Kamu harus mengisi ransel sedemikian sehingga total bobot barang TEPAT SAMA DENGAN W
(tidak boleh kurang dan tidak boleh lebih).
Tentukan total nilai maksimum yang bisa dicapai.
Jika tidak ada kombinasi barang yang memiliki total bobot tepat W, keluarkan -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Satu bilangan bulat: nilai maksimum pada bobot tepat W, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 200
1 <= W <= 50.000
1 <= w[i] <= W
1 <= v[i] <= 10^9

SAMPLE INPUT 1:
2 7
3 5
2 3

SAMPLE OUTPUT 1:
11
(Penjelasan: Ambil 1 barang bobot 3 (nilai 5) + 2 barang bobot 2 (nilai 3*2 = 6). Total bobot = 3 + 4 = 7. Total nilai = 5 + 6 = 11)

SAMPLE INPUT 2:
1 5
2 10

SAMPLE OUTPUT 2:
-1
(Penjelasan: Barang hanya berbobot 2, kelipatannya genap dan tidak bisa membentuk 5)
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

    vector<int> wt(n);
    vector<ll> val(n);
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }

    // TODO: Selesaikan dengan Exact Target Unbounded Knapsack
    // Inisialisasi vector<ll> dp(W + 1, -1);
    // dp[0] = 0;
    // Loop barang, loop kapasitas maju w dari wt[i] ke W:
    //   jika dp[w - wt[i]] != -1: dp[w] = max(dp[w], dp[w - wt[i]] + val[i])
    // Cetak dp[W]

    return 0;
}
