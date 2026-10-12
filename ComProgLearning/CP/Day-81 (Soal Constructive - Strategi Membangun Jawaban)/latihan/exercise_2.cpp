/*
============================================================
🏋️ Exercise 2: Tetangga Tidak Berurutan
============================================================
Day: 81 | Difficulty: Easy
Topic: Titik sambung antar blok
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n. Susun sebuah permutasi p dari bilangan 1 sampai n sehingga
untuk setiap dua posisi bertetangga, selisih nilainya TIDAK sama dengan 1.
Artinya, nilai mutlak dari p[i] dikurangi p[i-1] tidak boleh bernilai 1.
Kalau ada beberapa jawaban, cetak mana saja.
Kalau tidak ada, cetak -1.

📥 INPUT FORMAT:
- Satu baris berisi n

📤 OUTPUT FORMAT:
- n bilangan dipisah spasi, atau -1

📏 CONSTRAINTS:
- 1 <= n <= 2 * 10^5

📎 SAMPLE INPUT 1:
5

📎 SAMPLE OUTPUT 1:
2 4 1 3 5

📎 SAMPLE INPUT 2:
3

📎 SAMPLE OUTPUT 2:
-1

💡 HINT: Mulailah dengan mencari tahu untuk n mana saja soal ini mustahil.
         Kerjakan n = 1, 2, 3, 4 dengan tangan atau brute force. Jawabannya
         mungkin mengejutkanmu: ada dua nilai n yang mustahil, dan keduanya
         berurutan.
         Untuk konstruksinya, ide yang wajar adalah mengelompokkan bilangan
         menjadi dua blok sehingga di dalam tiap blok selisihnya minimal 2.
         Pengelompokan apa yang paling alami?
         Setelah kamu punya dua blok, ada satu tempat yang harus kamu
         periksa dengan sangat teliti: TITIK SAMBUNG di antara keduanya.
         Elemen terakhir blok pertama dan elemen pertama blok kedua juga
         bertetangga.
         Peringatan penting: ada DUA cara menyusun kedua blok itu, dan
         hanya SATU yang benar. Yang satunya gagal tepat pada satu nilai n
         saja. Kalau kamu hanya menguji n = 5, 6, 7 kamu tidak akan pernah
         menemukannya.
         Karena itu jalankan pemeriksamu untuk SELURUH n dari 1 sampai 200.

🎯 Learning Goals:
- [ ] Memeriksa titik sambung antar blok konstruksi
- [ ] Menguji seluruh n kecil, bukan beberapa pilihan
- [ ] Menemukan seluruh kasus mustahil dengan brute force
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: cari seluruh n yang mustahil dengan brute force

    // TODO: susun dua blok; periksa titik sambungnya

    return 0;
}
