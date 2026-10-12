/*
============================================================
📋 TUGAS 15: Hitung Subarray dengan Median Minimal X
============================================================
Source: Original
Difficulty: Hard
Topics: transformasi +1/-1 + prefix

PROBLEM:
Diberikan permutasi 1..N dan bilangan X. Hitung berapa banyak subarray
yang mediannya setidaknya X. Definisi median di sini: elemen ke-(k/2+1)
setelah subarray sepanjang k diurutkan.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: permutasi 1..N

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= X <= N <= 2*10^5

SAMPLE INPUT 1:
5 3
1 3 2 5 4

SAMPLE OUTPUT 1:
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ubah elemen >= X jadi +1 dan sisanya -1. Median >= X berarti jumlah subarray positif. Ini BUKAN sliding window - kenapa? Karena syaratnya tidak monoton; pakai prefix + hitungan (Day 29).

    return 0;
}
