/*
============================================================
📋 TUGAS 10: Multi-source BFS — Jarak ke Daratan Terdekat
============================================================
Source: LeetCode 1162 (As Far from Land as Possible) - inspired
Difficulty: Medium
Topics: multi-source BFS, grid

PROBLEM:
Diberikan grid N×N (N baris, N kolom):
  '1' = daratan
  '0' = lautan

Untuk setiap sel lautan, hitung jarak Manhattan-like
(langkah 4-arah) ke daratan terdekat.

Cetak jarak maksimum dari semua sel lautan ke daratan terdekat.
Jika tidak ada lautan atau tidak ada daratan, cetak -1.

INPUT FORMAT:
- Baris 1: integer N
- N baris berikutnya: string panjang N (hanya '0' dan '1')

OUTPUT FORMAT:
- Satu integer: jarak maksimum, atau -1

CONSTRAINTS:
- 1 ≤ N ≤ 100

SAMPLE INPUT 1:
4
0010
0000
0100
0000

SAMPLE OUTPUT 1:
3

SAMPLE INPUT 2:
3
111
010
111

SAMPLE OUTPUT 2:
1

NOTE: Multi-source BFS dari semua daratan sekaligus.
      Setiap lautan mendapat jarak ke daratan terdekat otomatis.
      Jawaban = max dari semua dist sel lautan.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
