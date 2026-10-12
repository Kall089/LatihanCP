/*
============================================================
📋 TUGAS 15: Segmen Terpanjang Tanpa Titik Terlarang
============================================================
Source: Original
Difficulty: Hard
Topics: kompresi + sort

PROBLEM:
Diberikan M titik terlarang pada garis bilangan dan sebuah rentang
[L, R]. Cari segmen bilangan bulat berurutan TERPANJANG di dalam [L, R]
yang tidak memuat satu pun titik terlarang. Cetak panjangnya.

INPUT FORMAT:
- Baris pertama: M, L, dan R
- Baris kedua: M titik terlarang

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 0 <= M <= 2*10^5
- -10^9 <= L <= R <= 10^9

SAMPLE INPUT 1:
3 1 10
3 7 8

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urutkan titik terlarang, buang yang di luar [L,R], lalu periksa celah antar titik berurutan termasuk celah di kedua ujung.

    return 0;
}
