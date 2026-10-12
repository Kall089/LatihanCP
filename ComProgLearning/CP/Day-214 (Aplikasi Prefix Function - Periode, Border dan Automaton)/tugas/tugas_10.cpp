/*
============================================================
📋 TUGAS 10: Hitung String yang Memuat Pola
============================================================
Source: Original
Difficulty: Medium
Topics: DP automaton

PROBLEM:
Hitung banyaknya string sepanjang L atas alfabet A huruf pertama yang MEMUAT
pola P setidaknya sekali. Cetak hasilnya modulo 1_000_000_007.

INPUT FORMAT:
- Baris pertama: L dan A
- Baris kedua: P

OUTPUT FORMAT:
- Satu bilangan mod 1e9+7

CONSTRAINTS:
- 1 <= L <= 2000
- 1 <= A <= 26
- 1 <= |P| <= 200

SAMPLE INPUT 1:
3 2
aa

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Komplemen: A^L dikurangi banyaknya string yang menghindari P.

    return 0;
}
