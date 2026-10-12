/*
============================================================
🏋️ Exercise 6: Menyusun Teks dari Stempel
============================================================
Day: 215 | Difficulty: Hard (Contest-level)
Topic: Z-matching + verifikasi cakupan interval
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Tavas punya sebuah stempel bertuliskan pola P dan selembar kertas kosong
sepanjang N. Ia menempelkan stempel itu tepat M kali pada posisi-posisi
p[1] < p[2] < ... < p[M] (1-based, posisi awal penempelan). Penempelan boleh
saling tumpang tindih; bagian yang tertumpuk harus konsisten (huruf yang sama).
Posisi kertas yang tidak pernah tertutup stempel boleh diisi huruf apa pun
dari 26 huruf kecil.
Hitung berapa banyak string berbeda sepanjang N yang mungkin dihasilkan,
modulo 1_000_000_007. Jika penempelan yang diberikan MUSTAHIL (dua penempelan
tumpang tindih tetapi memaksa huruf yang berbeda), cetak 0.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: string P
- Baris ketiga: M bilangan p[1..M] (kosong jika M = 0)

📤 OUTPUT FORMAT:
- Satu bilangan mod 1e9+7

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 0 <= M <= N
- 1 <= |P| <= N
- 1 <= p[1] < p[2] < ... < p[M] <= N - |P| + 1

📎 SAMPLE INPUT 1:
6 2
ioi
1 3

📎 SAMPLE OUTPUT 1:
26

📎 SAMPLE INPUT 2:
5 2
ioi
1 2

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Dua penempelan di posisi a < b tumpang tindih sepanjang
         |P| - (b - a) karakter. Tumpang tindih itu KONSISTEN persis ketika
         panjang tersebut merupakan border dari P — dan Z-function
         memberitahumu semua border dalam satu kali jalan.
         Sisanya: hitung posisi yang tidak tertutup, jawabannya 26^(bebas).

🎯 Learning Goals:
- [ ] Menghubungkan "tumpang tindih konsisten" dengan "border"
- [ ] Menghitung total posisi tertutup tanpa menandai satu per satu (O(N))
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    string p;
    cin >> p;

    // TODO: baca posisi

    // TODO: bangun z dari p, tandai panjang mana saja yang merupakan border

    // TODO: untuk tiap pasangan berurutan, cek apakah tumpang tindihnya valid

    // TODO: hitung posisi bebas, jawabannya 26^bebas mod 1e9+7

    return 0;
}
