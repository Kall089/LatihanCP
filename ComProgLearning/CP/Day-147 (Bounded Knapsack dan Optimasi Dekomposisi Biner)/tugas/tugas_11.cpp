/*
============================================================
📋 TUGAS 11: Koin Minimum Dua Kasir (Bounded Exchange)
============================================================
Source: Competitive Programming Classic
Difficulty: Hard
Topics: Bounded Knapsack Exchange, Kembalian Koin

PROBLEM:
Kamu ingin membayar sebuah barang seharga tepat X rupiah kepada kasir.
Kamu membawa N jenis koin, di mana koin jenis ke-i bernilai w[i] rupiah
dan kamu memiliki stok terbatas sebanyak c[i] keping.
Kasir memiliki koin yang sama namun dalam jumlah tak terbatas untuk memberikan uang kembalian.
Kamu boleh membayar dengan uang pas X, atau membayar dengan nominal Y >= X
lalu kasir memberikan kembalian (Y - X) rupiah menggunakan koin yang sama dengan keping minimum.

Tentukan jumlah minimum total keping koin yang berpindah tangan:
(koin yang kamu bayarkan ke kasir + koin kembalian dari kasir).
Jika transaksi mustahil dilakukan, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: jumlah total keping koin minimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 50
1 <= X <= 10.000
1 <= w[i] <= 1.000
1 <= c[i] <= 100

SAMPLE INPUT 1:
2 8
5 2
2 4

SAMPLE OUTPUT 1:
2
(Penjelasan: Kamu bayar dua keping 5 (total 10). Kasir kembalikan satu keping 2 (kembalian 2).
Total koin = 2 + 1 = 3 koin.
Tapi tunggu, jika kamu bayar empat keping 2 = 8 (uang pas 4 koin).
3 koin lebih sedikit dari 4 koin! Maka jawaban adalah 3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> w(n);
    vector<int> c(n);
    int max_w = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
        max_w = max(max_w, w[i]);
    }

    // TODO: Selesaikan Bounded Exchange Problem
    // 1. Tentukan batas nominal Y_max = x + max_w * max_w (atau x + 10000)
    // 2. DP 1: Bounded Knapsack Min Coins untuk pembayaran pembeli (stok c[i])
    // 3. DP 2: Unbounded Knapsack Min Coins untuk kembalian kasir (stok tak terbatas)
    // 4. Jawaban = min_{Y >= x} (dp_buyer[Y] + dp_change[Y - x])

    return 0;
}
