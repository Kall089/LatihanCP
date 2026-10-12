/*
============================================================
📋 TUGAS 10: Sisipkan Huruf jadi Palindrom
============================================================
Source: Original
Difficulty: Medium
Topics: akhiran palindromik

PROBLEM:
Berapa huruf MINIMAL yang harus ditambahkan di AWAL S agar S menjadi
palindrom? Cetak juga string palindrom hasilnya.
Perhatikan baik-baik ARAHNYA: menambah di awal bergantung pada AWALAN
palindromik terpanjang, sedangkan menambah di akhir bergantung pada
AKHIRAN palindromik terpanjang. Dua hal ini sangat sering tertukar.

INPUT FORMAT:
- Satu baris: string S

OUTPUT FORMAT:
- Baris 1: jumlah huruf tambahan
- Baris 2: palindrom hasilnya

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
aacecaaa

SAMPLE OUTPUT 1:
1
aaacecaaa
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Awalan palindromik terpanjang "aacecaaa" adalah "aacecaa" (7 huruf),
    // jadi 8 - 7 = 1 huruf perlu ditambahkan di awal.
    // Bandingkan dengan pendekatan pi di Day 214 dan catat mana yang lebih nyaman.

    return 0;
}
