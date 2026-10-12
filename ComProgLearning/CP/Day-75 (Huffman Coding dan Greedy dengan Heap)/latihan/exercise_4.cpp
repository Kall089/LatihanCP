/*
============================================================
🏋️ Exercise 4: Menghubungkan Kabel Bertingkat
============================================================
Day: 75 | Difficulty: Medium
Topic: K-ary Huffman + simpul dummy
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N berkas dengan ukuran a[i]. Sebuah mesin penggabung mampu
menggabungkan TEPAT K berkas sekaligus menjadi satu berkas, dengan biaya
sama dengan jumlah ukuran seluruh berkas yang digabungkan.
Kalau berkas yang tersisa kurang dari K, kamu boleh menggabungkan berkas
yang ada saja.
Proses berhenti ketika hanya tersisa satu berkas.
Cari TOTAL BIAYA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N ukuran a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 2 <= K <= 100
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5 3
1 2 3 4 5

📎 SAMPLE OUTPUT 1:
21

📎 SAMPLE INPUT 2:
4 2
1 2 3 4

📎 SAMPLE OUTPUT 2:
19

💡 HINT: Perluasan langsung dari Exercise 1: ambil K terkecil, bukan dua
         terkecil. Tulis itu dulu dan uji pada sampel 1 — hasilnya mungkin
         bukan 25.
         Masalahnya ada di penggabungan yang TIDAK PENUH. Kalau pada suatu
         langkah kamu hanya punya kurang dari K berkas, langkah itu boros.
         Pertanyaannya: langkah tidak penuh itu sebaiknya terjadi di AWAL
         atau di AKHIR? Pikirkan berkas mana yang ikut terhitung berkali-
         kali.
         Setelah kamu menjawabnya, kamu butuh cara memaksa langkah tidak
         penuh itu terjadi di tempat yang kamu mau. Trik yang lazim:
         tambahkan beberapa berkas berukuran nol.
         Berapa banyak yang harus ditambahkan? Setiap penggabungan mengubah
         K berkas menjadi 1, jadi mengurangi jumlah berkas sebanyak K-1.
         Dari sana kamu bisa menurunkan syaratnya sendiri.
         Sampel 2 memakai K = 2 sehingga hasilnya harus sama persis dengan
         Exercise 1 — pakai itu untuk memeriksa kodemu.

🎯 Learning Goals:
- [ ] Memperluas Huffman ke K arah
- [ ] Menurunkan syarat jumlah daun untuk pohon K-ary penuh
- [ ] Memakai simpul dummy sebagai alat
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung berapa dummy yang dibutuhkan

    // TODO: gabungkan K terkecil berulang kali

    return 0;
}
