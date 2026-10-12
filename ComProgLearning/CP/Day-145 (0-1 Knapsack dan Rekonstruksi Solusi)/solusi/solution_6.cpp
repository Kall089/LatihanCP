/*
============================================================
✅ Solution 6: Membagi Warisan Seadil Mungkin
============================================================
Approach: Subset sum + minimisasi |S - 2x|
Complexity: Time O(N · S) | Space O(S)
Key Insight: Masalah partisi menjadi dua bagian selalu bisa dinyatakan dalam
             SATU variabel saja. Kalau total seluruhnya S dan satu ahli waris
             menerima x, maka yang lain menerima S - x, dan selisihnya
             |x - (S - x)| = |S - 2x|.
             Jadi kita tidak perlu memikirkan dua bagian sekaligus -- cukup
             mencari x yang bisa dicapai dan meminimumkan |S - 2x|.

📖 MENGUBAHNYA MENJADI SOAL YANG SUDAH DIKENAL:
   "x bisa dicapai" berarti ada subhimpunan yang jumlahnya tepat x --
   dan itu persis subset sum dari Exercise 4.
   Setelah menandai seluruh x yang bisa dicapai, tinggal menyapu dan
   mengambil yang meminimumkan |S - 2x|.

📖 KENAPA MENYAPU SAMPAI S, BUKAN HANYA SAMPAI S/2:
   Secara matematis cukup memeriksa x <= S/2, karena |S - 2x| simetris di
   sekitar S/2. Memeriksa seluruh rentang juga benar dan menghindari
   kesalahan pembulatan saat S ganjil. Biayanya hanya faktor dua.

⚠️ BAGIAN KOSONG HARUS DIIZINKAN. Sampel 3 (satu benda bernilai 7)
   mengharuskan salah satu ahli waris menerima nol. Karena basis
   bisa[0] = 1 sudah menandai x = 0 sebagai tercapai, kasus ini tertangani
   otomatis -- tetapi hanya kalau kamu TIDAK mengeluarkan x = 0 dari
   pencarian (berbeda dari Exercise 4 yang memang meminta subhimpunan tidak
   kosong).
   Perbedaan kecil antara dua soal yang hampir sama; baca dengan teliti.

⚠️ ARAH LOOP MUNDUR, alasan yang sama seperti sebelumnya.

⚠️ BATAS ARRAY: total paling besar 100 x 1000 = 100000.

📖 KASUS KHUSUS YANG MENARIK: kalau S genap dan S/2 bisa dicapai, jawabannya
   0 -- pembagian sempurna. Sampel 1 (nilai [3,1,4,2,2], S = 12) memang
   begitu: {3,1,2} dan {4,2} keduanya berjumlah 6.
   Tetapi kamu TIDAK perlu memeriksa kasus itu secara terpisah; menyapu
   seluruh x sudah mencakupnya.

VERIFIKASI SAMPEL 2 (nilai [1, 100], S = 101):
   x yang bisa: 0, 1, 100, 101
   |101 - 0| = 101, |101 - 2| = 99, |101 - 200| = 99, |101 - 202| = 101
   minimum 99   ✓

🔄 ALTERNATIVE APPROACHES:
- Bitset: `bs |= bs << x` lalu sapu bitnya. 64 kali lebih cepat.
- Meet in the middle: kalau N <= 40 tetapi nilainya sangat besar (Day 54).
  Untuk soal ini, nilai kecil sehingga DP lebih baik.
- Soal ini adalah bentuk klasik "Partition Problem", dan varian LeetCode
  1049 (Last Stone Weight II) adalah soal yang sama persis dengan cerita
  berbeda -- pengenalan pola seperti ini sangat berharga.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    int S = 0;
    for (int& x : a) { cin >> x; S += x; }

    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;                                 // bagian KOSONG diizinkan

    for (int x : a)
        for (int c = S; c >= x; c--)             // MUNDUR
            if (bisa[c - x]) bisa[c] = 1;

    int best = S;                                // kasus terburuk: semua ke satu
    for (int x = 0; x <= S; x++)
        if (bisa[x]) best = min(best, abs(S - 2 * x));

    cout << best << '\n';
    return 0;
}
