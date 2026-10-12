/*
============================================================
📋 TUGAS 11: LCA dengan Euler Tour
============================================================
Source: Original
Difficulty: Hard
Topics: RMQ pada pohon

PROBLEM:
Diberikan pohon berakar dengan N simpul dan Q query berisi dua simpul.
Untuk setiap query, cetak leluhur bersama terdekat (LCA) keduanya.
Query harus dijawab O(1) setelah preprocessing.

INPUT FORMAT:
- Baris pertama: N dan Q
- N-1 baris: u dan v
- Q baris: u dan v

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 2
1 2
1 3
2 4
2 5
4 5
4 3

SAMPLE OUTPUT 1:
2
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Euler tour mengubah pohon jadi array kedalaman. LCA menjadi 'simpul berkedalaman MINIMUM pada rentang' - persis sparse table indeks. Materi lengkapnya Day 202.

    return 0;
}
