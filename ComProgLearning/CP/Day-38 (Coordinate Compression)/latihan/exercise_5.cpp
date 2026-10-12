/*
============================================================
🏋️ Exercise 5: Berapa Interval Menutupi Tiap Titik
============================================================
Day: 38 | Difficulty: Hard
Topic: Kompresi interval dengan r+1 + difference array
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N interval bilangan bulat [l, r]. Untuk setiap k dari 1 sampai N,
hitung ADA BERAPA BANYAK bilangan bulat yang tertutup oleh TEPAT k interval.
Sebagai contoh, dengan interval [1,3] dan [2,5]: bilangan 1 tertutup 1
interval, bilangan 2 dan 3 tertutup 2 interval, bilangan 4 dan 5 tertutup
1 interval. Jadi jawabannya: tepat 1 interval -> 3 bilangan,
tepat 2 interval -> 2 bilangan.
Koordinat bisa mencapai 10^9 sehingga kamu tidak bisa menandai satu per satu.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing l dan r

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan: jawaban untuk k = 1, 2, ..., N

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= l <= r <= 10^9

📎 SAMPLE INPUT 1:
3
0 3
1 3
3 8

📎 SAMPLE OUTPUT 1:
6 2 1

📎 SAMPLE INPUT 2:
2
1 3
2 5

📎 SAMPLE OUTPUT 2:
3 2

💡 HINT: Perlakukan setiap interval sebagai dua kejadian: "mulai di l"
         dan "berakhir SETELAH r", yaitu di r+1. Urutkan seluruh kejadian,
         lalu sapu sambil menjaga hitungan interval aktif.
         Di antara dua kejadian berurutan, hitungannya KONSTAN — jadi kamu
         bisa menambahkan seluruh panjang segmen itu sekaligus.
         Perhatikan bahwa r+1 muncul lagi di sini, dengan alasan yang sama
         seperti pada kompresi interval.

🎯 Learning Goals:
- [ ] Sweep line berbasis kejadian (+1 di l, -1 di r+1)
- [ ] Menambahkan kontribusi per SEGMEN, bukan per titik
- [ ] Memahami peran r+1 secara mendalam
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: buat daftar kejadian (l, +1) dan (r+1, -1)

    // TODO: urutkan kejadian berdasarkan koordinat

    // TODO: sapu; di antara koordinat berurutan, hitungan konstan

    return 0;
}
