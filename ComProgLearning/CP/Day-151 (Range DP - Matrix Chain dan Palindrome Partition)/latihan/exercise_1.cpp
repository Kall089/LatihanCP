/*
============================================================
🏋️ Exercise 1: Rantai Filter Citra Batik (Matrix Chain Multiplication)
============================================================
Day: 151 | Difficulty: Easy-Medium | Topic: Range DP Dasar
Source: Classic Matrix Chain Multiplication / AtCoder
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah laboratorium pengolahan citra batik harus mengalikan rantai N buah matriks filter
secara berurutan dalam urutan tetap: A[1] * A[2] * ... * A[N].
Matriks ke-i berukuran p[i-1] baris dan p[i] kolom.
Mengalikan matriks berukuran (a x b) dengan matriks berukuran (b x c) membutuhkan
a * b * c operasi perkalian skalar.

Perkalian matriks bersifat asosiatif: urutan pengelompokan tanda kurung tidak mengubah
hasil akhir matriks, namun sangat mempengaruhi jumlah total operasi perkalian skalar.
Tentukan jumlah operasi perkalian skalar MINIMUM yang dapat dicapai dengan memilih
urutan pengelompokan tanda kurung yang optimal. Urutan urutan matriks tidak boleh ditukar.

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N, menyatakan banyak matriks.
- Baris kedua berisi N + 1 bilangan bulat p[0], p[1], ..., p[N],
  di mana matriks ke-i berukuran p[i-1] x p[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: jumlah perkalian skalar minimum (gunakan 64-bit integer / long long).

📏 CONSTRAINTS:
- 1 <= N <= 180
- 1 <= p[i] <= 100.000

📎 SAMPLE INPUT 1:
3
10 30 5 60

📎 SAMPLE OUTPUT 1:
4500

[Penjelasan Sample 1:
Matriks A1(10x30), A2(30x5), A3(5x60).
- (A1 x A2) x A3:
  A1 x A2 butuh 10 * 30 * 5 = 1500 perkalian, hasil matriks (10x5).
  (A1 A2) x A3 butuh 10 * 5 * 60 = 3000 perkalian.
  Total = 1500 + 3000 = 4500 operasi.
- A1 x (A2 x A3):
  A2 x A3 butuh 30 * 5 * 60 = 9000 perkalian, hasil matriks (30x60).
  A1 x (A2 A3) butuh 10 * 30 * 60 = 18000 perkalian.
  Total = 9000 + 18000 = 27000 operasi.
Pilihan minimum adalah 4500.]

📎 SAMPLE INPUT 2:
1
7 11

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2: Hanya ada 1 matriks, tidak ada perkalian yang perlu dilakukan.]

📎 SAMPLE INPUT 3:
2
100000 100000 100000

📎 SAMPLE OUTPUT 3:
1000000000000000

[Penjelasan Sample 3: 100000^3 = 10^15 (butuh 64-bit long long)]

💡 HINT:
- State: dp[l][r] = biaya perkalian minimum untuk rantai matriks l sampai r (0-indexed).
- Base case: dp[i][i] = 0.
- Loop luar: panjang rantai `len` dari 2 sampai N.
- Loop dalam: coba seluruh titik pecah `k` dari l sampai r-1:
  dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + p[l] * p[k+1] * p[r+1]).

🎯 Learning Goals:
- [ ] Memahami struktur rekurens Range DP pada masalah Matrix Chain Multiplication.
- [ ] Mampu mengatur urutan evaluasi tabel berdasarkan panjang interval secara konsisten.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18; // Guard overflow

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    // TODO: Selesaikan Matrix Chain Multiplication dengan Range DP
    // 1. Inisialisasi vector<vector<ll>> dp(n, vector<ll>(n, 0))
    // 2. Loop len dari 2 s.d. n
    // 3. Loop l dari 0 s.d. n - len
    // 4. Loop k dari l s.d. r - 1
    // 5. Cetak dp[0][n-1]

    return 0;
}
