/*
============================================================
📋 TUGAS 11: Flowers (LIS Berbobot)
============================================================
Source: AtCoder Educational DP-Q
Difficulty: Hard
Topics: LIS berbobot + Fenwick prefix-max (Day 170)

PROBLEM:
N bunga berjajar, tinggi h[i] (permutasi 1..N) dan keindahan a[i].
Buang sebagian bunga sehingga tinggi yang TERSISA naik ketat dari kiri ke
kanan. Maksimalkan total keindahan.

INPUT: Baris 1 N; Baris 2 N tinggi; Baris 3 N keindahan
OUTPUT: satu bilangan (long long)
CONSTRAINTS: 1 <= N <= 2*10^5, 1 <= a[i] <= 10^9

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
4                          60
3 1 4 2
10 20 30 40
Penjelasan: ambil bunga ke-2 (tinggi 1, indah 20) dan ke-4 (tinggi 2, indah 40).

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
1                          10
1
10

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          3
3 2 1
1 2 3
Penjelasan: tinggi menurun, jadi hanya satu bunga yang boleh tersisa.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i] = a[i] + max{ dp[j] : h[j] < h[i], j < i }
    // Naif O(n^2). Untuk N=2*10^5 pakai FENWICK PREFIX-MAX atas h:
    //     query(h[i]-1) lalu update(h[i], dp[i]).
    // Perhatikan: BIT prefix-max hanya boleh dipakai kalau updatenya monoton
    // (nilai hanya membesar) -- di sini benar. Untuk min/max umum -> segment tree.
    return 0;}
