/*
============================================================
📋 TUGAS 15: Anagram Substring
============================================================
Source: Original
Difficulty: Hard
Topics: frekuensi + window + perbandingan vektor

PROBLEM:
Diberikan string S dan string P. Cari semua posisi awal (1-based) di dalam
S di mana terdapat substring sepanjang |P| yang merupakan ANAGRAM dari P.

INPUT FORMAT:
- Baris pertama: S
- Baris kedua: P

OUTPUT FORMAT:
- Posisi-posisi, dipisah spasi (kosong kalau tidak ada)

CONSTRAINTS:
- 1 <= |P| <= |S| <= 10^5

SAMPLE INPUT 1:
cbaebabacd
abc

SAMPLE OUTPUT 1:
1 7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Window ukuran tetap + dua array 26. Membandingkan 26 slot tiap langkah itu O(26n) - aman. Tapi ada cara lebih baik: jaga variabel 'berapa slot yang sudah cocok'.

    return 0;
}
