/*
============================================================
🏋️ Exercise 2: Total Waktu Server Sibuk
============================================================
Day: 73 | Difficulty: Easy
Topic: Total panjang gabungan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah server menerima N permintaan. Permintaan ke-i membuat server sibuk
dari detik s[i] sampai detik e[i]. Beberapa permintaan bisa berlangsung
bersamaan.
Server disebut SIBUK pada suatu saat kalau ada minimal satu permintaan yang
sedang diproses.
Cari TOTAL DURASI server dalam keadaan sibuk.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: s[i] dan e[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total durasi sibuk

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= s[i] < e[i] <= 10^9

📎 SAMPLE INPUT 1:
3
1 5
3 7
10 12

📎 SAMPLE OUTPUT 1:
8

📎 SAMPLE INPUT 2:
2
1 4
1 4

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Kalau kamu langsung menjumlahkan (e[i] - s[i]) untuk semua i,
         sampel 1 akan memberi 4 + 4 + 2 = 10, bukan 8. Waktu yang tumpang
         tindih terhitung dua kali.
         Jadi kamu perlu menghilangkan tumpang tindihnya lebih dulu.
         Exercise 1 baru saja memberimu alat untuk itu.
         Sampel 2 menguji kasus dua permintaan yang identik — pastikan
         kodemu menghitungnya sekali, bukan dua kali.
         Ada juga pendekatan kedua memakai difference array (Day 31) plus
         kompresi koordinat (Day 38). Tulis keduanya kalau sempat, lalu
         bandingkan hasilnya pada masukan acak. Kalau berbeda, salah satunya
         punya bug kasus tepi.

🎯 Learning Goals:
- [ ] Memakai hasil penggabungan sebagai alat, bukan sebagai tujuan
- [ ] Menyadari kesalahan menjumlahkan panjang secara langsung
- [ ] Mengenali dua pendekatan berbeda untuk soal yang sama
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hilangkan tumpang tindih lebih dulu

    // TODO: baru jumlahkan panjangnya

    return 0;
}
