/*
============================================================
📋 TUGAS 12: Cek Rotasi dengan Hash
============================================================
Source: Original
Difficulty: Hard
Topics: Hash pada string gandaan

PROBLEM:
Dua string A dan B disebut rotasi satu sama lain jika B bisa diperoleh
dengan memotong A di suatu titik lalu menukar kedua bagiannya.
Tentukan apakah B merupakan rotasi dari A, memakai hashing.

Petunjuk: B adalah rotasi A jika panjangnya sama DAN B muncul sebagai
substring di dalam A+A.

INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

OUTPUT FORMAT:
- Satu baris: "YA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |A|, |B| <= 10^5

SAMPLE INPUT 1:
abcde
cdeab

SAMPLE OUTPUT 1:
YA
============================================================
*/
#include <bits/stdc++.h>
#include <unordered_set>   // sebagian bits/stdc++.h tidak memuatnya
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ingat: long long, petakan huruf ke 1..26, dan +M sebelum modulo

    return 0;
}
