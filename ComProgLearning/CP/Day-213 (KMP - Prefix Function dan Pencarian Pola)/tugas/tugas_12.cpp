/*
============================================================
📋 TUGAS 12: Kemunculan pada Teks Panjang
============================================================
Source: Original
Difficulty: Hard
Topics: KMP matching

PROBLEM:
Cetak semua posisi kemunculan P di dalam T. Uji dengan teks yang punya
banyak awalan mirip agar terlihat kelebihan KMP dibanding pencarian naif.

INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

OUTPUT FORMAT:
- Satu baris: posisi-posisi kemunculan, atau -1.

CONSTRAINTS:
- 1 <= |P| <= |T| <= 10^6

SAMPLE INPUT 1:
mississippi
issi

SAMPLE OUTPUT 1:
2 5
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
