/*
============================================================
📋 TUGAS 11: Xor-Paths
============================================================
Source: CF 1006F
Difficulty: Hard
Topics: MITM pada grid

PROBLEM:
Grid R x C berisi bilangan. Dari sudut kiri atas ke sudut kanan bawah,
hanya boleh bergerak ke kanan atau ke bawah. Hitung berapa jalur yang
XOR seluruh selnya sama dengan K.

INPUT FORMAT:
- Baris pertama: R, C, dan K
- R baris berisi C bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 20
- 0 <= nilai, K < 2^62

SAMPLE INPUT 1:
3 3 11
2 1 5
7 10 0
12 6 4

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
    // Setiap jalur panjangnya R+C-1. Bangkitkan seluruh jalur separuh pertama dari kiri atas, dan separuh kedua dari kanan bawah secara MUNDUR, lalu cocokkan di diagonal tengah.

    return 0;
}
