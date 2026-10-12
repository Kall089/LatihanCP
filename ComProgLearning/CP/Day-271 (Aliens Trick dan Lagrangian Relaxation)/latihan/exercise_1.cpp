/*
============================================================
🏋️ Exercise 1: Beli dan Jual Saham dengan Maksimal K Transaksi
============================================================
Day: 271 | Difficulty: Medium | Topic: Aliens Trick (Lagrangian Relaxation)
Source: Best Time to Buy and Sell Stock IV
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan riwayat harga saham harian selama N hari: P[0], P[1], ..., P[N-1].
Kamu ingin memaksimalkan total keuntungan finansial dengan aturan:
1. Kamu boleh melakukan PALING BANYAK K transaksi jual-beli.
   Satu transaksi terdiri dari membeli satu lembar saham di hari i, dan menjualnya di hari j (j > i).
2. Kamu tidak boleh memegang lebih dari 1 saham secara bersamaan (harus menjual saham yang dipegang
   sebelum membeli saham baru).
3. Transaksi tidak wajib dilakukan jika pasar tidak menguntungkan.

Jika diselesaikan dengan DP berdimensi (hari, transaksi), waktu yang dibutuhkan adalah O(N * K).
Untuk N, K <= 200.000, pendekatan tersebut akan TLE.
Selesaikan masalah ini dengan ALIENS TRICK (WQS Binary Search) dalam waktu O(N log(MaxPrice))!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat non-negatif P[0], P[1], ..., P[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total keuntungan maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- 1 <= K <= N
- 0 <= P[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 2
2 4 1

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Beli di hari ke-0 (harga 2), jual di hari ke-1 (harga 4). Keuntungan = 4 - 2 = 2.
Maksimal transaksi K = 2 (kita hanya memakai 1 transaksi).]

📎 SAMPLE INPUT 2:
6 2
3 2 6 5 0 3

📎 SAMPLE OUTPUT 2:
7

[Penjelasan Sample 2:
Transaksi 1: Beli di hari ke-1 (harga 2), jual di hari ke-2 (harga 6) -> untung 4.
Transaksi 2: Beli di hari ke-4 (harga 0), jual di hari ke-5 (harga 3) -> untung 3.
Total keuntungan = 4 + 3 = 7.]

📎 SAMPLE INPUT 3:
5 1
5 4 3 2 1

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Harga terus menurun, opsi terbaik adalah tidak melakukan transaksi apapun (keuntungan 0).]

💡 HINT:
- Misalkan f(k) adalah keuntungan maksimum dengan paling banyak k transaksi.
- Fungsi f(k) bersifat konkaf (penambahan batas transaksi memberikan kenaikan keuntungan yang semakin berkurang).
- Terapkan penalti biaya transaksi lambda >= 0 untuk setiap kali kita menjual saham.
- DP tanpa batas transaksi dengan penalti lambda:
  free: keuntungan terbaik saat tidak memegang saham.
  hold: keuntungan terbaik saat sedang memegang saham.
  Transisi:
  new_free = max(free, hold + P[i] - lambda) -> transaksi selesai, count transaksi + 1
  new_hold = max(hold, free - P[i])
- Lakukan Binary Search pada nilai penalti lambda dalam rentang [0, 10^9].
- Keuntungan asli f(K) = free(lambda*) + K * lambda*.

🎯 Learning Goals:
- [ ] Memahami formulasi dasar Aliens Trick pada masalah batas operasi K.
- [ ] Mengimplementasikan DP status 1D bebas batasan K yang dievaluasi berulang kali oleh Binary Search.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Aliens Trick O(N log(MaxPrice))

    return 0;
}
