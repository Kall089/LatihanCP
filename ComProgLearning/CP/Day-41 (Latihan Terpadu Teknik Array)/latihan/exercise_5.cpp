/*
============================================================
🏋️ Exercise 5: Persegi Panjang Terbesar di Peta Ladang
============================================================
Day: 41 | Difficulty: Hard
Topic: monotonic stack (Day 36) + iterasi per baris (Day 30)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah ladang berbentuk grid R x C. Setiap petak bernilai '.' kalau subur
dan '#' kalau berbatu. Seorang petani ingin membangun gudang berbentuk
persegi panjang yang seluruh petaknya subur.

Cari LUAS persegi panjang subur terbesar yang bisa dibangun. Kalau seluruh
ladang berbatu, cetak 0.

Kuncinya adalah reduksi. Kalau kamu bisa menyelesaikan versi satu dimensi
(persegi panjang terbesar di dalam histogram), maka versi grid ini hanyalah
menjalankan versi 1D itu sebanyak R kali, dengan histogram yang diperbarui
secara inkremental per baris.

📥 INPUT FORMAT:
- Baris pertama: R dan C
- R baris berikutnya: masing-masing string sepanjang C berisi '.' atau '#'

📤 OUTPUT FORMAT:
- Satu bilangan: luas terbesar

📏 CONSTRAINTS:
- 1 ≤ R, C ≤ 1000

📎 SAMPLE INPUT 1:
4 5
..#..
.....
.###.
.....

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
3 3
###
###
###

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2 4
....
....

📎 SAMPLE OUTPUT 3:
8

📎 SAMPLE INPUT 4:
4 4
.#..
.#..
....
.#..

📎 SAMPLE OUTPUT 4:
8

💡 HINT: Untuk tiap baris i, hitung tinggi[j] = berapa banyak petak subur
         berturut-turut ke ATAS dari (i, j). Lalu selesaikan "persegi panjang
         terbesar di histogram" pada array tinggi itu memakai monotonic stack.

🎯 Learning Goals:
- [ ] Mereduksi masalah 2D menjadi R kali masalah 1D
- [ ] Menerapkan monotonic stack untuk batas kiri dan kanan sekaligus
- [ ] Menjaga kompleksitas tetap O(R·C), bukan O(R·C^2)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca R, C, dan grid

    // TODO: Siapkan array tinggi berukuran C, awalnya nol

    // TODO: Untuk tiap baris:
    //         perbarui tinggi[j] -> kalau petak subur, tinggi[j]++, kalau
    //         berbatu, tinggi[j] = 0
    //         lalu jalankan luasHistogram(tinggi) dan ambil maksimumnya

    // TODO: Tulis fungsi luasHistogram memakai monotonic stack.
    //       Trik umum: tambahkan tinggi 0 di ujung supaya stack pasti kosong
    //       di akhir, sehingga tidak perlu loop pembersihan terpisah.

    return 0;
}
