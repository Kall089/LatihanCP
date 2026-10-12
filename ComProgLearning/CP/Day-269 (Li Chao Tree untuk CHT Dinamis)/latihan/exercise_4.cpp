/*
============================================================
🏋️ Exercise 4: Relai Komunikasi Acak (Arbitrary Kalila & Dimna)
============================================================
Day: 269 | Difficulty: Hard | Topic: Li Chao Tree (Dynamic DP)
Source: Codeforces 319C Generalized (Unsorted Arrays)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N pos relai komunikasi bernomor 1 sampai N.
Pos 1 sudah aktif sejak awal dengan biaya pengaktifan 0.
Tujuanmu adalah mengaktifkan pos ke-N dengan total biaya seminimum mungkin.

Setiap pos i memiliki parameter a[i] dan b[i].
BERBEDA DENGAN DAY 268, NILAI a[i] DAN b[i] DI SINI TIDAK MEMILIKI JAMINAN MONOTON
(nilai a bisa naik-turun secara acak, dan nilai b juga bisa naik-turun secara acak).
Namun urutan indeks pos 1, 2, ..., N tetap terurut dari kiri ke kanan.

Untuk mengaktifkan pos i (i > 1), kamu harus memilih salah satu pos j yang sudah aktif sebelumnya (j < i).
Biaya pengaktifan pos i dari pos j adalah:
`Biaya(j, i) = dp[j] + b[j] * a[i]`.

Tentukan TOTAL BIAYA MINIMUM untuk mengaktifkan pos ke-N!

Selesaikan dengan LI CHAO TREE dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].
- Baris ketiga berisi N bilangan bulat b[0], b[1], ..., b[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum mengaktifkan pos N.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000 <= a[i], b[i] <= 1.000.000

📎 SAMPLE INPUT 1:
3
2 5 3
4 1 2

📎 SAMPLE OUTPUT 1:
12

[Penjelasan Sample 1:
Pos 0 (a=2, b=4): dp[0] = 0. Garis L0: y = 4x + 0.
Pos 1 (a=5, b=1): dp[1] = dp[0] + b[0]*a[1] = 0 + 4*5 = 20. Garis L1: y = 1x + 20.
Pos 2 (a=3, b=2):
- Pilihan 1 (dari pos 0): 0 + 4*3 = 12.
- Pilihan 2 (dari pos 1): 20 + 1*3 = 23.
Minimum = 12.]

📎 SAMPLE INPUT 2:
3
1 4 2
5 2 1

📎 SAMPLE OUTPUT 2:
10
(Pos 1 dp=0, garis 5x. Pos 2 (a=4): 5*4 = 20, garis 2x + 20. Pos 3 (a=2): 5*2 = 10, garis 1x + 10. Min = 10.)

💡 HINT:
- Kumpulkan seluruh nilai a[i] sebagai himpunan koordinat kueri Li Chao Tree.
- Rekurensi: `dp[i] = min_{j < i} (dp[j] + b[j] * a[i])`.
- Setiap pos j menghasilkan garis `y = b[j] * x + dp[j]`.
- Query titik x = a[i] menggunakan Li Chao Tree, lalu tambahkan garis milik pos i.

🎯 Learning Goals:
- [ ] Mengimplementasikan Li Chao Tree untuk DP linier tanpa monotonisitas.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
