/*
============================================================
📋 TUGAS 15: Bandingkan MITM dengan DP
============================================================
Source: Original
Difficulty: Hard
Topics: perbandingan empiris

PROBLEM:
Bangkitkan N barang acak dengan bobot di rentang [1, C/N] dan kapasitas C,
lalu selesaikan knapsack dengan DUA cara: DP O(N*C) dan meet in the middle.
Ukur waktu keduanya dan cetak dalam milidetik. Lakukan untuk beberapa
kombinasi N dan C, lalu simpulkan sendiri di mana titik peralihannya.

INPUT FORMAT:
- Baris pertama: N dan C

OUTPUT FORMAT:
- Dua bilangan: waktu DP dan waktu MITM

CONSTRAINTS:
- 1 <= N <= 40
- 1 <= C <= 10^7

SAMPLE INPUT 1:
30 100000

SAMPLE OUTPUT 1:
(bergantung mesin)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Coba N=30 C=1e4, lalu N=30 C=1e7, lalu N=40 C=1e12 (DP mustahil). Angkanya akan menunjukkan kenapa 'periksa batas bobot dulu' bukan saran kosong.

    return 0;
}
