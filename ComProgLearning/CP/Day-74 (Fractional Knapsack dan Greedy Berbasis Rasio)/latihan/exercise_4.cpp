/*
============================================================
🏋️ Exercise 4: Knapsack Bertingkat
============================================================
Day: 74 | Difficulty: Medium
Topic: Bounded knapsack + dekomposisi biner
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N jenis barang. Barang jenis ke-i memiliki berat w[i], nilai v[i], dan
tersedia sebanyak c[i] buah.
Barang TIDAK boleh dipotong, tetapi kamu boleh mengambil beberapa buah dari
jenis yang sama, paling banyak c[i] buah.
Kapasitas tas adalah W.
Cari NILAI TOTAL MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i], v[i], dan c[i]

📤 OUTPUT FORMAT:
- Satu bilangan: nilai maksimum

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^4
- 1 <= w[i] <= 10^4
- 1 <= v[i] <= 10^9
- 1 <= c[i] <= 10^4

📎 SAMPLE INPUT 1:
2 10
3 4 3
5 7 1

📎 SAMPLE OUTPUT 1:
12

📎 SAMPLE INPUT 2:
1 7
3 5 100

📎 SAMPLE OUTPUT 2:
10

💡 HINT: Pendekatan paling lurus: perlakukan tiap buah sebagai barang
         terpisah, lalu jalankan DP 0/1 biasa. Hitung dulu berapa total
         barang yang bisa muncul pada batasan terburuk, dan periksa apakah
         kompleksitasnya masih layak. Kamu akan menemukan bahwa tidak.
         Jadi kamu butuh cara memampatkan c[i] buah menjadi jauh lebih
         sedikit "barang gabungan".
         Kuncinya pertanyaan ini: dengan potongan berukuran 1, 2, 4, 8, ...
         berapa saja jumlah yang bisa kamu bentuk? Kalau kamu bisa membentuk
         setiap jumlah dari 0 sampai c[i], kamu tidak kehilangan apa pun.
         Perhatikan potongan TERAKHIR — ia tidak selalu berupa pangkat dua.
         Hitung nilainya dengan hati-hati agar totalnya tepat c[i].
         Sampel 2 menguji c yang jauh lebih besar dari yang bisa muat.

🎯 Learning Goals:
- [ ] Menghitung kompleksitas sebelum menulis kode
- [ ] Menguasai dekomposisi biner untuk bounded knapsack
- [ ] Menangani potongan terakhir dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: pecah tiap jenis menjadi potongan berukuran pangkat dua

    // TODO: jalankan DP 0/1 pada potongan-potongan itu

    return 0;
}
