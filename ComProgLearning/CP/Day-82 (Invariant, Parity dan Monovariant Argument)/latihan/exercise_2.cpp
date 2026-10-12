/*
============================================================
🏋️ Exercise 2: Menutup Papan dengan Domino
============================================================
Day: 82 | Difficulty: Easy
Topic: Pewarnaan papan catur
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada papan berukuran N kali M. Beberapa sel dilubangi sehingga tidak bisa
dipakai.
Kamu ingin menutup SELURUH sel yang tersisa dengan domino berukuran 1 kali 2
(boleh diletakkan mendatar atau tegak), tanpa tumpang tindih dan tanpa
keluar papan.
Tentukan apakah SYARAT PERLU untuk penutupan itu terpenuhi. Cetak "MUNGKIN"
kalau terpenuhi, atau "MUSTAHIL" kalau tidak.
(Perhatikan: kamu hanya diminta memeriksa syarat perlu, bukan menentukan
apakah penutupannya benar-benar ada.)

📥 INPUT FORMAT:
- Baris pertama: N, M, dan K (banyaknya lubang)
- K baris berikutnya: baris dan kolom tiap lubang (1-based)

📤 OUTPUT FORMAT:
- "MUNGKIN" atau "MUSTAHIL"

📏 CONSTRAINTS:
- 1 <= N, M <= 1000
- 0 <= K <= N * M
- Seluruh lubang berbeda

📎 SAMPLE INPUT 1:
8 8 2
1 1
8 8

📎 SAMPLE OUTPUT 1:
MUSTAHIL

📎 SAMPLE INPUT 2:
8 8 2
1 1
1 8

📎 SAMPLE OUTPUT 2:
MUNGKIN

📎 SAMPLE INPUT 3:
2 2 1
1 1

📎 SAMPLE OUTPUT 3:
MUSTAHIL

💡 HINT: Ada DUA syarat perlu yang harus kamu periksa, dan yang pertama
         jauh lebih mudah.
         Syarat pertama: setiap domino menutup tepat dua sel. Apa artinya
         bagi jumlah sel yang tersisa?
         Syarat kedua lebih menarik. Warnai papan seperti papan catur:
         sel di baris i kolom j berwarna sesuai paritas dari i ditambah j.
         Sekarang perhatikan: sebuah domino, bagaimanapun kamu letakkan,
         selalu menutup berapa sel putih dan berapa sel hitam?
         Dari situ kamu bisa menyimpulkan hubungan yang HARUS berlaku antara
         jumlah sel putih dan sel hitam yang tersisa.
         Sampel 1 adalah teka-teki paling terkenal dalam topik ini. Kedua
         sudut yang dilubangi kebetulan berwarna sama, sehingga
         keseimbangannya rusak.
         Sampel 2 memakai dua sudut yang berlainan warna, dan syarat
         perlunya lolos.
         Peringatan penting: kalau kedua syarat terpenuhi, itu TIDAK
         otomatis berarti penutupannya ada. Invarian membuktikan MUSTAHIL,
         bukan MUNGKIN. Karena itu soal ini hanya meminta syarat perlu.
         Kasus tepi: papan 1 kali 1, dan papan yang seluruh selnya dilubangi.

🎯 Learning Goals:
- [ ] Memakai pewarnaan sebagai invarian
- [ ] Membedakan syarat perlu dan syarat cukup
- [ ] Memeriksa syarat termurah lebih dulu
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: syarat pertama (paling murah)

    // TODO: syarat kedua lewat pewarnaan

    return 0;
}
