/*
============================================================
📋 TUGAS 08: Rolling Array
============================================================
Source: Latihan optimasi
Difficulty: Medium
Topics: memori O(C)

PROBLEM:
Hitung jalur dengan halangan pada grid H x W, TETAPI memori yang dipakai
harus O(W), bukan O(H*W).

INPUT: Baris 1 H W; H baris grid
OUTPUT: satu bilangan
CONSTRAINTS: 2 <= H, W <= 5000  (tabel penuh = 200 MB, MLE)

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
3 4                  3
...#
.#..
....

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
2 2                  0
.#
#.

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
3 3                  6
...
...
...
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[j] = dp[j] + dp[j-1]. Saat diproses, dp[j] masih nilai baris ATAS
    // dan dp[j-1] sudah baris SEKARANG.
    // LOOP j HARUS KIRI KE KANAN. Dibalik, dp[j-1] masih baris atas.
    return 0;}
