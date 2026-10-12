/*
============================================================
🏋️ Exercise 1: Palindrom Terpanjang
============================================================
Day: 216 | Difficulty: Easy
Topic: Manacher dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S, cari substring PALINDROM terpanjang di dalamnya.
Palindrom adalah string yang dibaca sama dari depan maupun belakang.
Jika ada beberapa palindrom terpanjang dengan panjang sama, cetak yang
posisi awalnya paling kiri.
Perhatikan bahwa palindrom bisa berpanjang genap maupun ganjil — solusimu
harus menangani keduanya. Solusi O(N^2) akan TLE.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu baris berisi substring palindrom terpanjang

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
abacaba

📎 SAMPLE OUTPUT 1:
abacaba

📎 SAMPLE INPUT 2:
abba

📎 SAMPLE OUTPUT 2:
abba

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:
a

💡 HINT: Sisipkan '#' di antara setiap huruf dan di kedua ujung. Setelah itu
         SEMUA palindrom berpanjang ganjil, dan kamu hanya butuh satu jenis
         pusat. Konversi baliknya: panjang asli = p[i],
         posisi awal = (i - p[i]) / 2.

🎯 Learning Goals:
- [ ] Menulis loop Manacher 11 baris dari nol
- [ ] Mendapatkan konversi indeks yang benar di percobaan pertama
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: bangun t = "#a#b#...#"

    // TODO: loop Manacher dengan c dan r
    //   - kalau i < r, salin dari cermin p[2*c - i] (ingat batasnya!)
    //   - ekspansi manual, cek DUA batas array
    //   - perbarui (c, r) kalau jangkauan melewati r

    // TODO: cari p[i] maksimum, konversi ke substring asli

    return 0;
}
