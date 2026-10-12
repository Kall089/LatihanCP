/*
============================================================
🏋️ Exercise 4: Cari Batas dengan Predikat
============================================================
Day: 49 | Difficulty: Medium
Topic: Kerangka first-true pada predikat non-perbandingan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pabrik punya N mesin. Mesin ke-i membutuhkan t[i] detik untuk
membuat satu produk, dan mesin-mesin bekerja secara bersamaan dan terus
menerus.
Diberikan target T produk, cari WAKTU MINIMUM (dalam detik) sehingga
seluruh mesin bersama-sama sudah menghasilkan setidaknya T produk.
Dalam waktu x detik, mesin ke-i menghasilkan floor(x / t[i]) produk.

📥 INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan t[i]

📤 OUTPUT FORMAT:
- Satu bilangan: waktu minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= T <= 10^9
- 1 <= t[i] <= 10^9

📎 SAMPLE INPUT 1:
3 7
3 2 5

📎 SAMPLE OUTPUT 1:
8

📎 SAMPLE INPUT 2:
1 1000000000
1000000000

📎 SAMPLE OUTPUT 2:
1000000000000000000

💡 HINT: Ruang pencariannya di sini bukan indeks array, melainkan NILAI
         waktu. Tetapi kerangkanya sama persis: cari nilai terkecil yang
         predikatnya bernilai true.
         Predikatnya: "dalam x detik, apakah total produk sudah mencapai T?"
         Predikat itu MONOTON — kalau x detik cukup, x+1 detik juga cukup.
         Dua peringatan: batas atas pencarianmu harus cukup besar (lihat
         sampel 2), dan penjumlahan produk bisa meluap kalau kamu tidak
         berhati-hati.

🎯 Learning Goals:
- [ ] Memakai kerangka yang sama pada ruang NILAI, bukan indeks
- [ ] Menentukan batas atas pencarian dengan benar
- [ ] Mencegah overflow saat mengevaluasi predikat
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tentukan lo dan hi. Seberapa besar hi harus?

    // TODO: predikat bisa(x): total floor(x / t[i]) >= T
    //       hati-hati: totalnya bisa jauh melebihi T

    return 0;
}
