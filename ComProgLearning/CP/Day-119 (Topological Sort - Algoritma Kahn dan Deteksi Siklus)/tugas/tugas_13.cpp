/*
============================================================
📋 TUGAS 13: Banyak Urutan Topologis (n kecil)
============================================================
Source: Klasik (DP bitmask)
Difficulty: Hard
Topics: DP bitmask di atas DAG

PROBLEM:
Hitung ADA BERAPA urutan topologis berbeda pada sebuah DAG dengan N <= 18
simpul. Cetak hasilnya modulo 10^9+7.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 18, 0 <= M <= N*(N-1)/2

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 0                    6

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 2                    1
1 2
2 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4 2                    6
1 2
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[mask] = banyak cara menyusun simpul di dalam mask.
    // Tambahkan simpul v ke mask hanya jika SEMUA pendahulunya sudah di mask.
    // Masalah ini #P-hard untuk n besar -- bitmask hanya jalan sampai n ~ 20.
    return 0;
}
