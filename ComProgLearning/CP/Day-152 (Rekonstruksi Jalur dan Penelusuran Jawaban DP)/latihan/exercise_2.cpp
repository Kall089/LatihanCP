/*
============================================================
🏋️ Exercise 2: Daftar Keping Terkecil (Coin Change Reconstruction)
============================================================
Day: 152 | Difficulty: Medium | Topic: Unbounded DP + Lexicographical Reconstruction
Source: Educational / Classic Coin Change Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Tersedia N jenis nilai keping koin yang berbeda dengan persediaan tak terbatas.
Kamu diminta membentuk nilai nominal tepat X menggunakan JUMLAH KEPING MINIMUM.

Di antara seluruh kemungkinan kombinasi keping yang menghasilkan jumlah keping minimum tersebut,
tentukan urutan nilai keping yang TERKECIL SECARA LEKSIKOGRAFIS.
Urutan keping merupakan bagian dari output, sehingga kamu bebas mengurutkan susunan keping
yang kamu gunakan demi mencapai urutan leksikografis terkecil.
(Dua urutan dibandingkan pada keping pertama yang berbeda; nilai keping yang lebih kecil menang).

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat berbeda c[0], c[1], ..., c[N-1], menyatakan nilai keping.

📤 OUTPUT FORMAT:
- Jika tidak mungkin membentuk nominal X, cetak `-1` saja.
- Jika mungkin:
  - Baris pertama: jumlah keping minimum K.
  - Baris kedua: K bilangan bulat menyatakan nilai keping yang digunakan, terurut leksikografis.
  - Khusus jika X = 0 (K = 0), baris kedua berupa string `EMPTY`.

📏 CONSTRAINTS:
- 1 <= N <= 50
- 0 <= X <= 3.000
- 1 <= c[i] <= 3.000
- Semua nilai c[i] saling berbeda.

📎 SAMPLE INPUT 1:
3 6
4 3 2

📎 SAMPLE OUTPUT 1:
2
2 4

[Penjelasan Sample 1:
Kombinasi yang berjumlah 6 dengan jumlah keping minimum (2 keping):
- [2, 4] -> 2 keping
- [3, 3] -> 2 keping
- [4, 2] -> 2 keping
Secara leksikografis, [2, 4] lebih kecil daripada [3, 3] dan [4, 2].]

📎 SAMPLE INPUT 2:
2 7
4 6

📎 SAMPLE OUTPUT 2:
-1

[Penjelasan Sample 2:
Hanya tersedia koin bernilai genap (4 dan 6), mustahil membentuk nominal ganjil 7.]

📎 SAMPLE INPUT 3:
2 0
3 9

📎 SAMPLE OUTPUT 3:
0
EMPTY

[Penjelasan Sample 3:
Nominal 0 membutuhkan 0 keping (K = 0), cetak EMPTY pada baris kedua.]

💡 HINT:
- Urutkan array koin `c` secara menaik di awal.
- Hitung DP 1D: dp[s] = banyak keping minimum untuk membentuk nominal s.
- Penelusuran maju:
  Di setiap sisa nominal `rem`:
  Iterasi koin `v` dari yang TERKECIL. Koin `v` layak jika:
  `v <= rem` dan `dp[rem] == dp[rem - v] + 1`.
  Pilih koin `v` pertama yang memenuhi kondisi ini, lalu kurangi `rem -= v`.

🎯 Learning Goals:
- [ ] Mengombinasikan Unbounded Coin Change DP dengan penelusuran leksikografis greedy-forward.
- [ ] Menangani kasus khusus nominal 0 (EMPTY) dan tak terjangkau (-1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // TODO: Selesaikan Coin Change Leksikografis
    // 1. Urutkan koin menaik
    // 2. Tabulasi dp[0..x]
    // 3. Rekonstruksi greedy dari koin terkecil

    return 0;
}
