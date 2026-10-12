/*
============================================================
🏋️ Exercise 3: Lampion dalam Lingkaran (Circular Knuth DP)
============================================================
Day: 270 | Difficulty: Hard | Topic: Knuth Optimization (Circular Array Doubling)
Source: Circular Sequential Merging
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N kelompok lampion yang tersusun melingkar di sekeliling panggung festival.
Kelompok ke-i memiliki bobot a[i].
Karena susunannya melingkar, kelompok pertama (indeks 0) dan kelompok terakhir (indeks N-1)
saling bertetangga dan dapat digabungkan langsung.

Aturan penggabungan sama persis dengan penggabungan berurutan:
- Pilih dua kelompok lampion bertetangga di lingkaran.
- Gabungkan menjadi satu kelompok dengan biaya sebesar total bobot kedua kelompok.
- Ulangi hingga seluruh lampion menjadi satu kelompok tunggal.
- Orientasi susunan melingkar tidak boleh dibalik atau diubah secara acak.

Tentukan TOTAL BIAYA MINIMUM untuk menggabungkan seluruh lampion dalam lingkaran!

Selesaikan dengan KNUTH OPTIMIZATION dengan ARRAY DOUBLING dalam waktu O(N^2)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat non-negatif a[0], a[1], ..., a[N-1] (mengikuti urutan lingkaran).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum.

📏 CONSTRAINTS:
- 1 <= N <= 1000
- 0 <= a[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
4 1 2 3

📎 SAMPLE OUTPUT 1:
19

[Penjelasan Sample 1:
Penggabungan terbaik:
- (1 + 2) = 3 (biaya 3), sisa [4, (3), 3]
- ((3) + 3) = 6 (biaya 6), sisa [4, (6)]
- (4 + (6)) = 10 (biaya 10), total = 3 + 6 + 10 = 19.]

📎 SAMPLE INPUT 2:
1
8

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2
2 5

📎 SAMPLE OUTPUT 3:
7

💡 HINT:
- Dalam susunan melingkar, pada operasi penggabungan terakhir, selalu ada TEPAT SATU pasangan batas
  yang TIDAK PERNAH digabungkan sebelum operasi terakhir.
- Ini berarti masalah lingkaran ekivalen dengan memotong lingkaran menjadi rantai linier di salah satu dari N titik potong.
- Alih-alih menjalankan algoritma linier N kali (yang akan memakan waktu O(N^3)), kita gandakan array menjadi ukuran 2N:
  `A[0..2N-1] = A[0..N-1] ++ A[0..N-1]`.
- Jalankan Knuth DP satu kali pada array ukuran 2N, tetapi HANYA UNTUK PANJANG INTERVAL len <= N!
- Jawaban akhir adalah minimum dari `dp[l][l + N - 1]` untuk semua 0 <= l < N.
- Total kompleksitas waktu tetap O(N^2)!

🎯 Learning Goals:
- [ ] Menguasai teknik penggandaan array (*array doubling*) untuk masalah DP melingkar.
- [ ] Membatasi panjang evaluasi len <= N agar Knuth Optimization tetap berjalan dalam O(N^2).
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

    // TODO: Selesaikan dengan Circular Knuth DP O(N^2)

    return 0;
}
