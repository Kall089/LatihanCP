/*
============================================================
📋 TUGAS 10: Rekonstruksi Ranking
============================================================
Source: Klasik (Sequence Reconstruction, LC 444 varian)
Difficulty: Medium
Topics: keunikan urutan topologis

PROBLEM:
Ada N pemain. Diberi M hasil pertandingan "a b" artinya a mengalahkan b.
Tentukan apakah ranking lengkap 1..N dapat ditentukan SECARA UNIK.
Cetak rankingnya jika unik, "AMBIGU" jika ada lebih dari satu, "TIDAK
KONSISTEN" jika ada siklus.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b

OUTPUT FORMAT:
- N bilangan, atau AMBIGU, atau TIDAK KONSISTEN

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    1 2 3
1 2
2 3
1 3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 1                    AMBIGU
1 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 3                    TIDAK KONSISTEN
1 2
2 3
3 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Cek q.size() > 1 di setiap iterasi.
    return 0;
}
