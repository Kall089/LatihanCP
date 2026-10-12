/*
============================================================
🏋️ Exercise 2: Susun Bilangan Terbesar
============================================================
Day: 71 | Difficulty: Easy
Topic: Menemukan komparator lewat dua elemen
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan bulat non-negatif. Susun seluruhnya berdampingan
(tanpa mengubah digit di dalam masing-masing bilangan) sehingga membentuk
satu bilangan yang SEBESAR MUNGKIN.
Cetak bilangan hasil susunan itu.
Perhatikan bahwa hasilnya bisa sangat panjang, sehingga kamu harus
memperlakukannya sebagai string, bukan sebagai bilangan.
Jika hasilnya berupa nol (misalnya seluruh masukan nol), cetak "0" saja
tanpa nol di depan.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi bilangan hasil susunan

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5
3 30 34 5 9

📎 SAMPLE OUTPUT 1:
9534330

📎 SAMPLE INPUT 2:
2
0 0

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Godaan pertama adalah "urutkan menurun sebagai bilangan". Uji itu
         pada dua bilangan 3 dan 30, lalu periksa apakah hasilnya benar.
         Kalau tidak, kamu butuh kriteria yang berbeda.
         Pertanyaan yang membuka jawabannya: kalau HANYA ada dua bilangan
         x dan y, bagaimana kamu memutuskan mana yang lebih dulu? Kamu
         hanya punya dua kemungkinan susunan — bandingkan keduanya secara
         langsung sebagai STRING.
         Jawaban dari pertanyaan itu langsung menjadi komparator untuk
         seluruh array.
         Sampel 2 ada untuk menguji satu kasus tepi yang mudah terlewat.

🎯 Learning Goals:
- [ ] Menurunkan komparator dari perbandingan dua elemen
- [ ] Menyadari kenapa "urut menurun" gagal
- [ ] Menangani kasus tepi nol di depan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca sebagai string

    // TODO: komparator yang membandingkan dua kemungkinan gabungan

    // TODO: tangani kasus hasil berupa nol semua

    return 0;
}
