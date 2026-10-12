/*
============================================================
📋 TUGAS 10: Kolam Renang
============================================================
Source: Original
Difficulty: Medium
Topics: geometri sederhana + binary search

PROBLEM:
Sebuah kolam berbentuk persegi panjang berukuran W x H. Kamu menuangkan
V satuan volume air. Kolam itu MIRING: kedalamannya bertambah secara linier
dari 0 di satu ujung sampai D di ujung lainnya. Cari ketinggian permukaan
air. Cetak 6 desimal.

INPUT FORMAT:
- Satu baris: W, H, D, dan V

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 1 <= W, H, D <= 1000
- 0 <= V <= W*H*D

SAMPLE INPUT 1:
10 10 10 250

SAMPLE OUTPUT 1:
5.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Volume air sebagai fungsi ketinggian bersifat MONOTON NAIK. Turunkan rumusnya (ada dua kasus: air belum melewati ujung dangkal, dan sudah), lalu binary search.

    return 0;
}
