/*
============================================================
📋 TUGAS 14: Posisi Kosong Berikutnya
============================================================
Source: Original
Difficulty: Hard
Topics: trik DSU sebagai penunjuk

PROBLEM:
Ada N slot bernomor 1..N yang mula-mula kosong. Ada Q permintaan; setiap
permintaan ingin menempati slot p, tetapi kalau p sudah terisi ia akan
mengambil slot KOSONG PERTAMA setelah p. Kalau tidak ada slot kosong
sampai N, permintaan itu ditolak (cetak -1). Cetak slot yang diperoleh
setiap permintaan.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: Q bilangan p

OUTPUT FORMAT:
- Q bilangan

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 5
1 1 2 5 5

SAMPLE OUTPUT 1:
1
2
3
5
-1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Pakai DSU di mana par[i] berarti 'slot kosong pertama mulai dari i'. Setelah memakai slot p, set par[p] = p+1.

    return 0;
}
