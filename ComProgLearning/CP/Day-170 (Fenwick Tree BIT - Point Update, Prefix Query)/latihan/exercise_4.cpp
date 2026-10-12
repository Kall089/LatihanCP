/*
============================================================
🏋️ Exercise 4: Update Rentang, Baca Satu Titik
============================================================
Day: 170 | Difficulty: Medium
Topic: BIT atas difference array
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan dan Q operasi:
- "1 a b u" : tambahkan u ke SETIAP elemen pada posisi a sampai b (inklusif).
- "2 k"     : cetak nilai pada posisi k.
Seluruh posisi 1-based.
Perhatikan bahwa sekarang yang diperbarui adalah RENTANG, sedangkan yang
dibaca adalah SATU TITIK — kebalikan dari Exercise 1.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: operasi

📤 OUTPUT FORMAT:
- Satu baris untuk setiap operasi jenis 2

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- 1 <= nilai <= 10^9
- -10^9 <= u <= 10^9

📎 SAMPLE INPUT 1:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

📎 SAMPLE OUTPUT 1:
5
6

💡 HINT: Struktur hari ini secara alami melakukan "update titik, query
         prefiks". Soal ini meminta kebalikannya — tetapi ada trik yang
         mengubah satu masalah menjadi yang lain.
         Ingat kembali difference array dari Day 31: kalau kamu menyimpan
         SELISIH antar elemen berdampingan alih-alih nilainya, maka
         menambahkan sesuatu ke sebuah rentang hanya menyentuh DUA posisi.
         Dan kalau kamu menjumlahkan seluruh selisih dari awal sampai
         posisi k, apa yang kamu dapatkan?
         Gabungkan kedua pengamatan itu.
         Satu hal teknis: salah satu dari dua posisi yang kamu sentuh bisa
         melebihi N. Pikirkan bagaimana menanganinya dengan aman.

🎯 Learning Goals:
- [ ] Membalik peran BIT lewat difference array
- [ ] Menyadari bahwa dua teknik lama bisa digabungkan menjadi yang baru
- [ ] Menangani indeks yang melebihi batas array
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: BIT menyimpan SELISIH, bukan nilai

    // TODO: rangeAdd menyentuh dua posisi

    // TODO: pointQuery adalah query prefiks

    return 0;
}
