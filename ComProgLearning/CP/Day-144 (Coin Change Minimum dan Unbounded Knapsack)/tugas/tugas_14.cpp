/*
============================================================
📋 TUGAS 14: Pembayaran Dua Arah (Koin dengan Kembalian)
============================================================
Source: Codeforces / Classic DP
Difficulty: Hard
Topics: Bidirectional Coin Change Minimum

PROBLEM:
Kamu ingin membeli sebuah barang seharga tepat X di sebuah toko.
Toko dan kamu sama-sama memiliki akses tak terbatas ke N pecahan koin c[0], ..., c[N-1].
Kamu membayar kasir dengan sejumlah koin (total nilai Y >= X), lalu kasir
mengembalikan uang kembalian sebesar (Y - X) juga menggunakan pecahan koin yang sama.

Tentukan jumlah minimum total koin yang berpindah tangan:
(jumlah koin yang kamu bayarkan + jumlah koin kembalian dari kasir).
Jika transaksi mustahil dilakukan, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: jumlah total koin minimum yang berpindah tangan, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 50
1 <= X <= 10.000
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
2 8
5 2

SAMPLE OUTPUT 1:
3
(Penjelasan: Kamu bayar dua koin 5 (total 10). Kasir mengembalikan satu koin 2 (kembalian 2). Total koin = 2 + 1 = 3 koin. Lebih sedikit dari membayar empat koin 2 = 4 koin)

SAMPLE INPUT 2:
1 7
2

SAMPLE OUTPUT 2:
-1
(Penjelasan: Selisih antara pembayaran kelipatan 2 dan kembalian kelipatan 2 selalu genap, tidak mungkin bernilai 7 ganjil)
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

    vector<int> c(n);
    int max_c = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        max_c = max(max_c, c[i]);
    }

    // TODO: Selesaikan dengan DP Coin Change Min
    // 1. Tentukan batas atas limit = x + max_c * max_c (atau minimal x + 20000).
    // 2. Hitung dp[v] = koin minimum untuk membentuk nilai v.
    // 3. Jawaban adalah min_{y >= x} (dp[y] + dp[y - x]).

    return 0;
}
