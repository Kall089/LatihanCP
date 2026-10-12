/*
============================================================
🏋️ Exercise 2: Deteksi Sisi yang Membentuk Siklus
============================================================
Day: 134 | Difficulty: Easy
Topic: unite yang mengembalikan bool
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan graf tak berarah dengan N simpul yang dibangun dengan menambahkan
M sisi satu per satu, dalam urutan yang diberikan.
Sebuah sisi disebut REDUNDAN jika pada saat ditambahkan, kedua ujungnya
SUDAH terhubung (sehingga sisi itu membentuk siklus).
Cetak indeks (1-based) seluruh sisi yang redundan, dipisah spasi. Jika tidak
ada, cetak baris kosong.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- M baris berikutnya: masing-masing u dan v

📤 OUTPUT FORMAT:
- Satu baris berisi indeks sisi redundan (boleh kosong)

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= M <= 2 * 10^5

📎 SAMPLE INPUT 1:
4 5
1 2
2 3
1 3
3 4
1 4

📎 SAMPLE OUTPUT 1:
3 5

📎 SAMPLE INPUT 2:
3 2
1 2
2 3

📎 SAMPLE OUTPUT 2:


💡 HINT: Kamu tidak perlu memeriksa keterhubungan secara terpisah sebelum
         menggabungkan. Kalau operasi penggabunganmu memberi tahu APAKAH ia
         benar-benar menggabungkan sesuatu, informasi itu sudah cukup —
         dan mendapatkannya gratis.
         Perhatikan bahwa sisi yang menghubungkan simpul ke dirinya sendiri
         (u sama dengan v) juga redundan menurut definisi di atas.
         Kebiasaan membuat operasi penggabungan mengembalikan nilai boolean
         akan sangat berguna di Exercise 5 nanti.

🎯 Learning Goals:
- [ ] Memakai nilai kembalian unite alih-alih memanggil find dua kali
- [ ] Mengenali deteksi siklus sebagai penerapan langsung DSU
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: unite yang mengembalikan bool

    // TODO: kalau mengembalikan false, sisi itu redundan

    return 0;
}
