/*
============================================================
🏋️ Exercise 1: Rata-rata Tertinggi Periode Tetap
============================================================
Day: 41 | Difficulty: Easy
Topic: prefix sum (Day 29) + sliding window ukuran tetap (Day 33)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah stasiun cuaca mencatat suhu selama N hari berturut-turut. Suhu boleh
bernilai negatif. Seorang peneliti ingin mengetahui periode K hari berurutan
mana yang rata-rata suhunya paling tinggi.

Cetak JUMLAH suhu pada periode terbaik itu (bukan rata-ratanya), agar
jawabannya tetap bilangan bulat. Kalau ada beberapa periode dengan jumlah
sama, cetak indeks awal yang paling kecil.

Soal ini menggabungkan dua hal: prefix sum untuk menghitung jumlah rentang
dalam O(1), dan gagasan jendela ukuran tetap yang bergeser.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan bulat, suhu tiap hari

📤 OUTPUT FORMAT:
- Dua bilangan: jumlah terbaik, lalu indeks awal periode (1-based)

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 2·10^5
- -10^9 ≤ suhu ≤ 10^9

📎 SAMPLE INPUT 1:
7 3
1 -2 5 6 -1 2 3

📎 SAMPLE OUTPUT 1:
10 3

📎 SAMPLE INPUT 2:
5 5
-1 -2 -3 -4 -5

📎 SAMPLE OUTPUT 2:
-15 1

📎 SAMPLE INPUT 3:
6 2
4 0 4 0 4 0

📎 SAMPLE OUTPUT 3:
4 1

💡 HINT: Jumlah jendela yang bergeser satu langkah = jumlah lama + elemen baru
         - elemen yang keluar. Tidak perlu menjumlah ulang K elemen.

🎯 Learning Goals:
- [ ] Menghitung jumlah rentang dalam O(1)
- [ ] Menggeser jendela tanpa menghitung ulang
- [ ] Menangani tie-breaking indeks terkecil
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan K, lalu array suhu

    // TODO: Bangun prefix sum ATAU geser jendela secara langsung
    // Hint: sum(l..r) = P[r+1] - P[l], dengan P berukuran N+1

    // TODO: Cari jendela dengan jumlah maksimum, simpan indeks awalnya
    // Hint: pakai > (bukan >=) supaya indeks terkecil yang tersimpan

    return 0;
}
