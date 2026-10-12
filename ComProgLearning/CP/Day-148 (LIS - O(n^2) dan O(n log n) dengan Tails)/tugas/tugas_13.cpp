/*
============================================================
📋 TUGAS 13: Longest Common Increasing Subsequence
============================================================
Source: SPOJ LCIS / CF 10D
Difficulty: Hard
Topics: gabungan LCS (Day 149) dan LIS

PROBLEM:
Diberi dua array A (panjang N) dan B (panjang M). Cari subsekuens terpanjang
yang merupakan subsekuens KEDUANYA sekaligus NAIK KETAT. Cetak panjangnya
lalu salah satu barisannya.

INPUT: Baris 1 N; Baris 2 A; Baris 3 M; Baris 4 B
OUTPUT: dua baris
CONSTRAINTS: 1 <= N, M <= 500

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
4                          2
2 3 1 6                    3 6
4
3 6 2 1

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
3                          0
1 2 3                      (baris kosong)
3
9 8 7

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          3
1 2 3                      1 2 3
3
1 2 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[j] = LCIS terpanjang yang BERAKHIR di B[j].
    // Loop i atas A; pelihara "best" = max dp[j] untuk B[j] < A[i] sejauh ini.
    // Saat A[i] == B[j]: dp[j] = best + 1.
    // O(N*M) dengan satu variabel bergulir -- trik yang layak dihafal.
    return 0;}
