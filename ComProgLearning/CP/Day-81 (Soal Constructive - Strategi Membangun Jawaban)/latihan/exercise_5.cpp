/*
============================================================
🏋️ Exercise 5: Matriks Baris dan Kolom Seimbang
============================================================
Day: 81 | Difficulty: Hard
Topic: Konstruksi berpola pada objek dua dimensi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n yang dijamin GANJIL. Susun sebuah matriks berukuran n kali n
yang memuat setiap bilangan dari 1 sampai n kuadrat TEPAT SEKALI, sehingga
JUMLAH setiap baris sama besar DAN jumlah setiap kolom juga sama besar
(dan sama dengan jumlah baris).
Diagonal tidak diperhitungkan.
Kalau ada beberapa jawaban, cetak mana saja.

📥 INPUT FORMAT:
- Satu baris berisi n (dijamin ganjil)

📤 OUTPUT FORMAT:
- n baris, masing-masing berisi n bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= n <= 499
- n dijamin ganjil

📎 SAMPLE INPUT 1:
3

📎 SAMPLE OUTPUT 1:
1 5 9
6 7 2
8 3 4

📎 SAMPLE INPUT 2:
1

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Hitung dulu berapa SEHARUSNYA jumlah tiap baris. Total seluruh
         bilangan dari 1 sampai n kuadrat punya rumus tertutup, dan ada n
         baris. Angka itu memberi target yang jelas untuk diperiksa.
         Sekarang untuk konstruksinya. Bayangkan setiap bilangan dari 1
         sampai n kuadrat ditulis sebagai (a dikali n) ditambah b ditambah
         1, dengan a dan b masing-masing dari 0 sampai n-1. Setiap pasangan
         (a, b) muncul tepat sekali, jadi kamu cukup menentukan a dan b
         untuk tiap sel.
         Syarat agar seluruh bilangan muncul tepat sekali: pemetaan dari
         (baris, kolom) ke (a, b) harus satu-satu.
         Sekarang pikirkan apa yang membuat jumlah baris sama. Kalau pada
         setiap baris, nilai a mengambil SELURUH nilai 0 sampai n-1 tepat
         sekali, dan nilai b juga begitu, maka jumlah tiap baris pasti
         sama. Hal yang sama berlaku untuk kolom.
         Jadi kamu butuh dua rumus untuk a dan b yang masing-masing
         membentuk persegi Latin, dan yang KOMBINASINYA tidak pernah
         berulang.
         Petunjuk kuat: coba a bergantung pada penjumlahan indeks, dan b
         bergantung pada pengurangan indeks, keduanya modulo n.
         Kenapa soal ini menjamin n ganjil? Coba konstruksimu untuk n = 2
         dan lihat apa yang terjadi. Lalu buktikan bahwa n = 2 memang
         mustahil dengan mencoba seluruh kemungkinan.
         Tulis pemeriksa yang memvalidasi TIGA hal: seluruh bilangan muncul
         tepat sekali, semua jumlah baris sama, dan semua jumlah kolom sama.
         Jalankan untuk seluruh n ganjil dari 1 sampai 59.

🎯 Learning Goals:
- [ ] Menghitung target sebelum membangun
- [ ] Memakai dua persegi Latin yang saling ortogonal
- [ ] Menulis pemeriksa untuk objek dua dimensi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung target jumlah tiap baris

    // TODO: tentukan a dan b untuk tiap sel

    // TODO: pemeriksa untuk mengujimu sendiri

    return 0;
}
