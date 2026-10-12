/*
============================================================
🏋️ Exercise 1: Permutasi Tanpa Titik Tetap
============================================================
Day: 81 | Difficulty: Easy
Topic: Konstruksi pola + kasus mustahil
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n. Susun sebuah permutasi p dari bilangan 1 sampai n sehingga
untuk SETIAP posisi i berlaku p[i] tidak sama dengan i.
Kalau ada beberapa jawaban, cetak mana saja.
Kalau tidak ada, cetak -1.

📥 INPUT FORMAT:
- Satu baris berisi n

📤 OUTPUT FORMAT:
- n bilangan dipisah spasi, atau -1

📏 CONSTRAINTS:
- 1 <= n <= 2 * 10^5

📎 SAMPLE INPUT 1:
4

📎 SAMPLE OUTPUT 1:
2 3 4 1

📎 SAMPLE INPUT 2:
1

📎 SAMPLE OUTPUT 2:
-1

💡 HINT: Sebelum apa pun, tulis PEMERIKSA. Fungsi yang menerima keluaranmu
         dan memeriksa tiga hal: ukurannya benar, isinya permutasi yang sah
         (tidak ada duplikat, tidak ada yang di luar rentang), dan syarat
         soal terpenuhi.
         Kamu akan memakai pemeriksa ini untuk menguji SELURUH n dari 1
         sampai 200, bukan beberapa n pilihan. Soal constructive punya
         banyak jawaban benar, jadi membandingkan keluaranmu dengan contoh
         di soal TIDAK BISA dipakai untuk menguji.
         Sekarang untuk konstruksinya: kapan soal ini mustahil? Pikirkan
         n = 1 lebih dulu, lalu yakinkan dirimu bahwa n = 2 dan seterusnya
         selalu mungkin.
         Untuk n yang mungkin, ada konstruksi yang sangat sederhana: geser
         semuanya satu langkah. Tuliskan rumusnya dengan hati-hati agar
         indeksnya tidak keluar rentang.
         Sampel 1 memberikan 2 3 4 1, tetapi 4 3 2 1 juga benar. Pastikan
         kamu tidak mencoba mencocokkan keluaranmu dengan itu.

🎯 Learning Goals:
- [ ] Menulis pemeriksa sebelum menulis konstruksi
- [ ] Mengenali kasus mustahil paling sederhana
- [ ] Menyadari bahwa jawaban benar tidak tunggal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tulis pemeriksa lebih dulu (di luar submit, untuk mengujimu sendiri)

    // TODO: periksa kemustahilan

    // TODO: konstruksi

    return 0;
}
