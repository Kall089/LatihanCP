/*
============================================================
📋 TUGAS 04: Kapan MITM Tidak Perlu
============================================================
Source: Original
Difficulty: Easy
Topics: analisis pemilihan alat

PROBLEM:
Diberikan T deskripsi soal knapsack, masing-masing berisi N (banyak barang)
dan C (kapasitas). Untuk setiap deskripsi, tentukan pendekatan mana yang
paling tepat: BRUTE (N <= 20), MITM (N <= 40 dan C > 10^7), DP (C <= 10^7),
atau TIDAK_BISA (selain itu). Prioritaskan BRUTE, lalu DP, lalu MITM.

INPUT FORMAT:
- Baris pertama: T
- T baris: N dan C

OUTPUT FORMAT:
- T baris

CONSTRAINTS:
- 1 <= T <= 1000

SAMPLE INPUT 1:
3
15 1000000000
30 1000
40 1000000000000

SAMPLE OUTPUT 1:
BRUTE
DP
MITM
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Melatih POHON KEPUTUSAN sebelum menulis kode. MITM bukan selalu jawaban terbaik untuk n <= 40.

    return 0;
}
