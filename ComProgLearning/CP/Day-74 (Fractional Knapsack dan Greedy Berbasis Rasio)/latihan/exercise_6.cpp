/*
============================================================
🏋️ Exercise 6: Knapsack dengan Kapasitas Raksasa
============================================================
Day: 74 | Difficulty: Hard (Contest-level)
Topic: Memilih dimensi DP + batas atas fractional
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N barang dengan berat w[i] dan nilai v[i]. Barang tidak boleh dipotong
dan tiap barang hanya boleh diambil sekali.
Kapasitas tas adalah W.
Cari NILAI TOTAL MAKSIMUM.

Perhatikan batasannya baik-baik: W sangat besar, tetapi TOTAL NILAI seluruh
barang tidak besar.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Satu bilangan: nilai maksimum

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^9
- 1 <= w[i] <= 10^9
- 1 <= v[i] <= 1000
- Jumlah seluruh v[i] tidak melebihi 10^5

📎 SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

📎 SAMPLE OUTPUT 1:
10

📎 SAMPLE INPUT 2:
2 1000000000
1000000000 1000
1000000000 1000

📎 SAMPLE OUTPUT 2:
1000

💡 HINT: DP knapsack biasa memakai kapasitas sebagai dimensi tabel. Di sini
         kapasitasnya sampai 10^9, sehingga tabelnya mustahil dibuat.
         Tapi lihat batasan yang lain: total seluruh nilai paling besar
         10^5. Batasan yang mencolok seperti ini hampir selalu disengaja.
         Pertanyaan yang membuka jawabannya: apa yang terjadi kalau kamu
         MENUKAR peran berat dan nilai di dalam tabel DP? Alih-alih
         bertanya "nilai maksimum untuk kapasitas c", tanyakan sesuatu yang
         diindeks oleh nilai.
         Setelah kamu merumuskan ulang, pikirkan apa yang harus
         diminimalkan, apa nilai awal tabelnya, dan bagaimana kamu membaca
         jawabannya di akhir.
         Hati-hati dengan nilai sentinel: jangan memakai sesuatu yang bisa
         meluap saat ditambah berat.
         Sebagai bonus, hitung juga batas atas fractional dari seluruh
         barang dan periksa bahwa jawabanmu tidak pernah melebihinya. Itu
         pemeriksaan kewarasan yang murah dan sering menangkap bug.

🎯 Learning Goals:
- [ ] Memilih dimensi DP berdasarkan batasan yang mencolok
- [ ] Membalik peran "yang dioptimalkan" dan "yang diindeks"
- [ ] Memakai batas atas fractional sebagai pemeriksaan kewarasan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: rumuskan ulang DP dengan NILAI sebagai indeks

    // TODO: tentukan nilai awal dan cara membaca jawabannya

    return 0;
}
