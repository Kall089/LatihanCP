/*
============================================================
🏋️ Exercise 4: Di Mana Minimumnya
============================================================
Day: 169 | Difficulty: Medium
Topic: Sparse table yang menyimpan indeks
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan dan Q pertanyaan rentang [a, b]
(1-based, inklusif). Untuk setiap pertanyaan, cetak INDEKS (1-based) dari
elemen terkecil pada rentang itu.
Jika ada beberapa elemen bernilai sama-sama terkecil, cetak indeks yang
PALING KIRI.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: a dan b

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
6 3
5 1 9 1 7 2
1 6
3 6
2 4

📎 SAMPLE OUTPUT 1:
2
4
2

💡 HINT: Alih-alih menyimpan NILAI minimum di dalam tabel, simpanlah INDEKS
         tempat minimum itu berada. Saat menggabungkan dua blok, kamu
         membandingkan NILAI pada kedua indeks itu lalu mengambil indeks
         pemenangnya.
         Perhatikan aturan seri: soal meminta indeks paling kiri. Saat dua
         nilai sama, indeks mana yang harus kamu pilih, dan operator
         perbandingan apa yang menghasilkan itu secara otomatis?
         Hati-hati: karena kedua blok pada query bisa TUMPANG TINDIH, aturan
         seri harus konsisten antara tahap pembangunan dan tahap query.
         Kalau tidak, kamu bisa mendapat indeks yang benar nilainya tetapi
         salah posisinya.
         Struktur ini adalah dasar dari salah satu cara menghitung LCA pada
         pohon dalam O(1) per query — kamu akan bertemu lagi di Day 202.

🎯 Learning Goals:
- [ ] Menyimpan indeks alih-alih nilai
- [ ] Menjaga konsistensi aturan seri di build dan query
- [ ] Mengenal fondasi LCA berbasis RMQ
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sp menyimpan INDEKS, bukan nilai

    // TODO: bandingkan lewat a[indeks], perhatikan aturan seri

    return 0;
}
