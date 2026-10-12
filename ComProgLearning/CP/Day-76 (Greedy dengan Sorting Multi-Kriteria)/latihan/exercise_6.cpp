/*
============================================================
🏋️ Exercise 6: Boneka Rusia
============================================================
Day: 76 | Difficulty: Hard (Contest-level)
Topic: Tie-break yang mengubah soal 2D menjadi 1D
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N amplop; amplop ke-i berukuran lebar w[i] dan tinggi h[i].
Sebuah amplop bisa dimasukkan ke dalam amplop lain kalau lebar DAN
tingginya benar-benar LEBIH KECIL (strict pada kedua ukuran).
Cari PANJANG RANTAI TERPANJANG, yaitu jumlah amplop maksimum yang bisa
disusun bersarang satu di dalam yang lain.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: w[i] dan h[i]

📤 OUTPUT FORMAT:
- Satu bilangan: panjang rantai terpanjang

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= w[i], h[i] <= 10^9

📎 SAMPLE INPUT 1:
4
5 4
6 4
6 7
2 3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3
4 4
4 4
4 4

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Soal ini adalah gabungan dua hal yang sudah kamu kuasai:
         pengurutan multi-kriteria dan barisan naik terpanjang.
         Idenya: urutkan menurut lebar, lalu soalnya menjadi mencari
         barisan naik terpanjang pada tinggi saja. Tapi ada satu masalah
         besar.
         Masalahnya: amplop dengan lebar SAMA tidak boleh bersarang.
         Kalau kamu mengurutkan tinggi secara menaik saat lebar seri,
         algoritma barisan naik akan salah memilih dua amplop berlebar
         sama sebagai rantai yang sah.
         Bagaimana cara membuat algoritma barisan naik "menolak" mereka
         secara otomatis? Petunjuk: kalau tinggi diurutkan MENURUN dalam
         kelompok berlebar sama, apa yang terjadi pada barisan naik?
         Trik ini adalah salah satu pemakaian tie-break paling elegan
         yang akan kamu temui, dan pola yang sama muncul di banyak soal
         lain.
         Untuk barisan naik terpanjang yang cepat, ingat bahwa ada versi
         O(n log n) memakai pencarian biner. Perhatikan bahwa di sini
         kamu butuh versi STRICT (naik tegas), bukan tidak turun —
         itu menentukan lower_bound atau upper_bound.
         Sampel 2 adalah kasus tepi: seluruh amplop identik, jadi tidak
         ada yang bisa bersarang.

🎯 Learning Goals:
- [ ] Memakai tie-break untuk mereduksi soal 2D menjadi 1D
- [ ] Menyadari bahwa tie-break bisa menegakkan batasan secara otomatis
- [ ] Membedakan barisan naik strict dan tidak turun
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan; tie-break yang membuat lebar sama otomatis ditolak

    // TODO: barisan naik terpanjang pada dimensi kedua

    return 0;
}
