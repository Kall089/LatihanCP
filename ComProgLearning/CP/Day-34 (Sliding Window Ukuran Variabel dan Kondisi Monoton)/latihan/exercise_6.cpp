/*
============================================================
🏋️ Exercise 6: Blok Seragam Terpanjang Setelah Penggantian
============================================================
Day: 34 | Difficulty: Hard (Contest-level)
Topic: Window + frekuensi mayoritas
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N yang hanya terdiri dari huruf besar 'A'..'Z',
dan sebuah bilangan K. Kamu boleh mengganti PALING BANYAK K karakter di dalam
S dengan huruf apa pun (setiap penggantian bebas memilih huruf).
Setelah penggantian, cari SUBSTRING TERPANJANG yang seluruh karakternya sama.
Cetak panjangnya.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: string S

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= K <= N

📎 SAMPLE INPUT 1:
4 2
AABA

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
7 1
AABABBA

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
3 0
ABC

📎 SAMPLE OUTPUT 3:
1

💡 HINT: Untuk sebuah window, berapa karakter yang harus diganti agar seluruh
         isinya seragam? Jawabannya lebar window dikurangi frekuensi karakter
         yang PALING SERING muncul di window itu. Window layak kalau angka itu
         tidak melebihi K.
         Catatan menarik: kamu tidak perlu menghitung ulang frekuensi
         maksimum saat menyusutkan window — pikirkan kenapa jawabannya
         tetap benar meski maxFreq sedikit "kedaluwarsa".

🎯 Learning Goals:
- [ ] Menerjemahkan "boleh mengubah K" menjadi kondisi window
- [ ] Memahami kenapa maxFreq yang tidak diturunkan tetap menghasilkan
      jawaban yang benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: cnt[26], l = 0, maxFreq = 0, best = 0

    // TODO: masukkan s[r], perbarui maxFreq

    // TODO: while ((r - l + 1) - maxFreq > K) keluarkan s[l], l++

    // TODO: best = max(best, r - l + 1)

    return 0;
}
