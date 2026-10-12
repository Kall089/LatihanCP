/*
============================================================
📋 TUGAS 12: Frog Jump dengan K Besar (Monotonic Deque)
============================================================
Source: Varian AtCoder DP-B
Difficulty: Hard
Topics: minimum jendela geser

PROBLEM:
N batu, biaya melompat dari i ke j adalah c[j] (biaya MASUK batu j, tidak
bergantung pada i). Boleh melompat sampai K ke depan. Cari biaya minimum
sampai batu N-1. Di sini K bisa sampai 10^5, jadi O(N*K) TLE.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N bilangan c
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 2 <= N <= 2*10^5, 1 <= K <= N, 0 <= c[i] <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 2                    3
0 1 2 1 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
5 4                    2
0 5 5 5 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1                    7
0 7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i] = min(dp[i-K..i-1]) + c[i].
    // Karena c[i] TIDAK bergantung pada asal lompatan, minimumnya bisa
    // diambil dengan MONOTONIC DEQUE (Day 37) dalam O(1) amortisasi -> O(N).
    // Inilah alasan biaya dibuat tidak bergantung i: ia bisa dikeluarkan dari
    // min. Pikirkan kenapa |h[i]-h[j]| TIDAK bisa diperlakukan begitu.
    return 0;
}
