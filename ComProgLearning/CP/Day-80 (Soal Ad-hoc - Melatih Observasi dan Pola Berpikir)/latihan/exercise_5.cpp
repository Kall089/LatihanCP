/*
============================================================
🏋️ Exercise 5: Menemukan Rumus dari Barisan
============================================================
Day: 80 | Difficulty: Hard
Topic: Mencari pola lalu memverifikasinya
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Definisikan f(n) sebagai banyaknya cara menyusun bilangan 1 sampai n dalam
satu baris sehingga TIDAK ADA bilangan yang menempati posisi aslinya
(artinya bilangan ke-i tidak boleh berada di posisi ke-i).
Diberikan n, cetak f(n) modulo 10^9 + 7.

📥 INPUT FORMAT:
- Satu baris berisi n

📤 OUTPUT FORMAT:
- Satu bilangan: f(n) modulo 10^9 + 7

📏 CONSTRAINTS:
- 1 <= n <= 10^7

📎 SAMPLE INPUT 1:
4

📎 SAMPLE OUTPUT 1:
9

📎 SAMPLE INPUT 2:
1

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2

📎 SAMPLE OUTPUT 3:
1

💡 HINT: Jangan mencoba menurunkan rumusnya dari nol. Lakukan ini sebagai
         gantinya:
         (1) tulis brute force yang mencoba SELURUH permutasi untuk n
             sampai 9 atau 10;
         (2) cetak barisannya, lalu cetak juga selisih pertama, selisih
             kedua, dan RASIO antar suku berurutan;
         (3) lihat mana di antara ketiganya yang menunjukkan pola.
         Kalau selisih pertama tetap, rumusnya linear. Kalau selisih kedua
         tetap, kuadrat. Kalau rasio tetap, eksponensial. Kalau rasio
         mendekati n, curigai sesuatu yang melibatkan faktorial.
         Setelah menemukan dugaan, VERIFIKASI untuk n yang lebih besar dari
         yang kamu pakai menebak. Kalau kamu menebak dari 5 suku,
         verifikasi sampai 10.
         Perhatikan batasan n sampai 10^7. Itu berarti kamu butuh rekurensi
         yang bisa dihitung dalam satu sapuan, bukan rumus dengan
         penjumlahan bersarang.
         Berhati-hatilah dengan suku bertanda negatif dalam aritmetika
         modular. Menambahkan MOD sebelum mengambil sisa adalah kebiasaan
         yang menyelamatkan.
         Periksa n = 1 dan n = 2 secara terpisah.

🎯 Learning Goals:
- [ ] Memakai brute force sebagai penemu rumus
- [ ] Membaca selisih dan rasio untuk menebak bentuk rumus
- [ ] Menangani bilangan negatif dalam aritmetika modular
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: temukan rumusnya secara empiris lebih dulu

    // TODO: verifikasi, lalu implementasikan rekurensinya

    return 0;
}
