/*
============================================================
🏋️ Exercise 6: Penukaran Mata Uang Minimum & Banyak Cara (Coin Change Synthesis)
============================================================
Day: 154 | Difficulty: Medium | Topic: Unbounded DP Synthesis
Source: Review Synthesis / Classic Coin Change
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah loket penukaran mata uang asing memiliki N jenis koin dengan pecahan c[0], c[1], ..., c[N-1].
Persediaan setiap jenis koin dianggap tidak terbatas.
Seorang nasabah ingin menukarkan uang sejumlah tepat X.

Kamu diminta menyelesaikan DUA TUGAS sekaligus:
1. Hitung JUMLAH KOIN MINIMUM yang dibutuhkan untuk membentuk nominal tepat X.
2. Hitung BANYAK KOMBINASI CARA BERBEDA untuk membentuk nominal tepat X, modulo 1.000.000.007!
   (Dua kombinasi dianggap sama jika susunan koin yang dipakai sama tanpa mempedulikan urutan pengambilan).

Jika nominal X TIDAK BISA dibentuk sama sekali dengan koin-koin yang ada, cetak `-1 0`.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat positif c[0], ..., c[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi dua bilangan bulat dipisahkan spasi:
  [jumlah koin minimum] [banyak kombinasi cara modulo 1.000.000.007].
  Jika mustahil, cetak `-1 0`.

📏 CONSTRAINTS:
- 1 <= N <= 100
- 0 <= X <= 100.000
- 1 <= c[i] <= 100.000

📎 SAMPLE INPUT 1:
3 11
1 2 5

📎 SAMPLE OUTPUT 1:
3 11

[Penjelasan Sample 1:
1. Koin minimum: 5 + 5 + 1 = 3 koin.
2. Banyak kombinasi cara untuk membentuk 11 adalah 11 cara.]

📎 SAMPLE INPUT 2:
2 3
2 4

📎 SAMPLE OUTPUT 2:
-1 0

[Penjelasan Sample 2:
Semua koin bernilai genap, tidak mungkin membentuk nominal ganjil 3.]

📎 SAMPLE INPUT 3:
1 0
10

📎 SAMPLE OUTPUT 3:
0 1

[Penjelasan Sample 3:
Target nominal X = 0.
Butuh 0 koin, dan ada tepat 1 cara (tidak mengambil koin apa pun).]

💡 HINT:
- Koin Minimum:
  - `min_coins[s]` = jumlah koin minimum untuk nominal s.
  - Inisialisasi dengan `INF`, `min_coins[0] = 0`.
  - Loop koin, lalu loop nominal MAJU dari `c` ke `X`:
    `min_coins[s] = min(min_coins[s], min_coins[s - c] + 1)`.
- Banyak Kombinasi Cara (Unordered):
  - `ways[s]` = banyak cara membentuk nominal s.
  - Inisialisasi dengan `0`, `ways[0] = 1`.
  - Loop koin di luar, loop nominal MAJU di dalam:
    `ways[s] = (ways[s] + ways[s - c]) % MOD`.
- Jika `min_coins[X] >= INF`, cetak `-1 0`.

🎯 Learning Goals:
- [ ] Memahami perbedaan perlakuan DP nilai ekstrem (minimum koin) vs DP kombinasi counting (banyak cara).
- [ ] Mengingat aturan urutan perulangan loop untuk kombinasi unik tanpa permutasi urutan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    // TODO: Selesaikan Coin Change Min Coins & Way Counting

    return 0;
}
