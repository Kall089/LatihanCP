/*
============================================================
📋 TUGAS 06: Reverse Engineering
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Pikirkan dari belakang

PROBLEM:
Mulai dari pasangan (1, 1). Operasi: ganti (x, y) menjadi (x+y, y) atau (x, y+x).
Cari langkah minimum untuk mencapai (a, b), atau -1.

INPUT FORMAT:
Baris 1: a dan b

OUTPUT FORMAT:
Satu bilangan, atau -1

CONSTRAINTS:
1 <= a, b <= 10^18

SAMPLE INPUT 1:
5 3

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
    // Maju bercabang dua, mundur hanya satu kemungkinan. Setelah dibalik, ini algoritma Euclid. Perhatikan bahwa jumlah pengurangan yang aman adalah (a-1)/b, bukan a/b.

    return 0;
}
