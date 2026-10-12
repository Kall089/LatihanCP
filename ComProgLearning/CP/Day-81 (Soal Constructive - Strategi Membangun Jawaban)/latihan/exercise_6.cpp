/*
============================================================
🏋️ Exercise 6: Barisan dengan Selisih yang Ditentukan
============================================================
Day: 81 | Difficulty: Hard (Contest-level)
Topic: Konstruksi dengan syarat ketat + pembuktian mustahil
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n dan k. Susun sebuah permutasi p dari bilangan 1 sampai n
sehingga himpunan nilai mutlak selisih antar tetangga, yaitu himpunan
{ |p[2]-p[1]|, |p[3]-p[2]|, ..., |p[n]-p[n-1]| }, memuat TEPAT k nilai
BERBEDA.
Kalau ada beberapa jawaban, cetak mana saja.
Kalau tidak ada, cetak -1.

📥 INPUT FORMAT:
- Satu baris berisi n dan k

📤 OUTPUT FORMAT:
- n bilangan dipisah spasi, atau -1

📏 CONSTRAINTS:
- 1 <= n <= 10^5
- 1 <= k <= n

📎 SAMPLE INPUT 1:
5 4

📎 SAMPLE OUTPUT 1:
1 5 2 4 3

📎 SAMPLE INPUT 2:
3 1

📎 SAMPLE OUTPUT 2:
1 2 3

📎 SAMPLE INPUT 3:
2 2

📎 SAMPLE OUTPUT 3:
-1

💡 HINT: Mulailah dari dua ujung ekstrem, karena keduanya paling mudah.
         Untuk k sama dengan 1: susunan apa yang membuat SELURUH selisih
         tetangga bernilai sama? Ini yang paling mudah.
         Untuk k sebesar mungkin: berapa nilai selisih berbeda yang bisa
         kamu capai paling banyak? Perhatikan bahwa selisih terbesar yang
         mungkin adalah n dikurangi 1, dan selisih terkecil adalah 1.
         Berapa banyak selisih yang tersedia seluruhnya, dan berapa banyak
         tetangga yang ada?
         Dua pengamatan itu memberi batas atas untuk k, dan dari situ kamu
         tahu kapan soal ini mustahil.
         Untuk konstruksi k maksimum, ada pola yang sangat terkenal: mulai
         dari salah satu ujung, lalu melompat bolak-balik ke ujung yang
         berlawanan, mengecil setiap kali. Tuliskan beberapa suku pertama
         untuk n = 5 dan lihat selisih-selisih yang dihasilkannya.
         Untuk k di antara kedua ekstrem, gabungkan keduanya: pakai pola
         melompat untuk bagian awal secukupnya, lalu lanjutkan dengan pola
         berurutan biasa yang tidak menambah selisih baru.
         Berhati-hatilah pada TITIK SAMBUNG antara kedua bagian itu —
         selisih di situ mungkin memperkenalkan nilai baru yang tidak kamu
         hitung.
         Uji dengan pemeriksa untuk SELURUH pasangan (n, k) dengan n sampai
         50.

🎯 Learning Goals:
- [ ] Menyelesaikan kasus ekstrem lebih dulu, lalu menggabungkannya
- [ ] Menurunkan batas atas parameter untuk menemukan kasus mustahil
- [ ] Mengawasi titik sambung pada konstruksi gabungan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: selesaikan k = 1 dan k maksimum lebih dulu

    // TODO: gabungkan; awasi titik sambungnya

    return 0;
}
