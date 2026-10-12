/*
============================================================
📋 TUGAS 05: Flight Discount
============================================================
Source: CSES 1195
Difficulty: Medium
Topics: dist[v][0/1]

PROBLEM:
N kota, M penerbangan satu arah berbiaya. Kamu boleh MEMOTONG SETENGAH biaya
tepat SATU penerbangan (dibulatkan ke bawah). Cari biaya minimum dari 1 ke N.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b c

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 2 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= c <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 4                    2
1 2 3
2 3 1
1 3 7
2 1 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    5
1 2 10

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 2                    3
1 2 4
2 3 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dist[v][0] = belum pakai diskon, dist[v][1] = sudah.
    // Relaksasi: [0]->[0] bayar penuh, [0]->[1] bayar w/2, [1]->[1] bayar penuh.
    return 0;
}
