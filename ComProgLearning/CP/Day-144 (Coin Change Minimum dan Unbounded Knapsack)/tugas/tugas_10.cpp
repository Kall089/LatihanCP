/*
============================================================
📋 TUGAS 10: Pengisian Kapasitas Gudang Gandum
============================================================
Source: Competitive Programming Classic
Difficulty: Medium
Topics: Unbounded Knapsack with Range Capacity

PROBLEM:
Sebuah truk pengangkut memiliki kapasitas muatan maksimum W kg.
Terdapat N jenis karung gandum. Karung jenis ke-i memiliki berat w[i] kg
dan nilai keuntungan v[i] rupiah.
Setiap jenis karung gandum tersedia dalam jumlah tak terbatas.
Truk hanya diizinkan berangkat jika total muatannya tidak melebihi W kg
dan sisa ruang kosongnya tidak lebih dari S kg (dengan kata lain,
total berat muatan harus berada dalam rentang [W - S, W]).

Tentukan keuntungan maksimum yang dapat diperoleh. Jika tidak ada kombinasi
karung yang beratnya berada dalam rentang [W - S, W], keluarkan -1.

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, W, dan S.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Satu bilangan bulat: keuntungan maksimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 200
1 <= W <= 10.000
0 <= S <= W
1 <= w[i] <= W
1 <= v[i] <= 10^9

SAMPLE INPUT 1:
2 10 2
4 7
3 5

SAMPLE OUTPUT 1:
17
(Penjelasan: Rentang berat yang sah adalah [8, 10]. Ambil satu karung 4 dan dua karung 3: total berat = 4 + 3 + 3 = 10 (sah), total keuntungan = 7 + 5 + 5 = 17)

SAMPLE INPUT 2:
1 5 1
3 10

SAMPLE OUTPUT 2:
-1
(Penjelasan: Rentang yang sah adalah [4, 5]. Berat kelipatan 3 yang mungkin adalah 0, 3, 6, ... Tidak ada yang berada di [4, 5])
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W, S;
    if (!(cin >> n >> W >> S)) return 0;

    vector<int> wt(n);
    vector<ll> val(n);
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }

    // TODO: Selesaikan dengan Unbounded Knapsack
    // Gunakan dp[w] = nilai maksimum tepat pada bobot w (inisialisasi -1, dp[0] = 0).
    // Cari nilai maksimum di antara dp[w] untuk w dari W - S sampai W.

    return 0;
}
