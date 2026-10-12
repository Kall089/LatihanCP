/*
============================================================
📋 TUGAS 07: Cek Rotasi
============================================================
Source: Original
Difficulty: Medium
Topics: KMP pada string gandaan

PROBLEM:
Dua string A dan B disebut rotasi satu sama lain jika B bisa diperoleh
dengan memotong A di suatu titik lalu menukar kedua bagiannya.
Tentukan apakah B merupakan rotasi dari A.
Petunjuk: B rotasi A jika |A| == |B| dan B muncul di dalam A+A.

INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

OUTPUT FORMAT:
- Satu baris: "YA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |A|, |B| <= 10^5

SAMPLE INPUT 1:
abcde
deabc

SAMPLE OUTPUT 1:
YA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ingat inti KMP: j = pi[j - 1], dan indeks teks tidak pernah mundur

    return 0;
}
