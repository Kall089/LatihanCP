/*
============================================================
📋 TUGAS 15: Segmen Terpanjang dengan Rata-rata Minimal X
============================================================
Source: Original
Difficulty: Hard
Topics: prefix + transformasi

PROBLEM:
Diberikan array N bilangan dan bilangan X. Cari SEGMEN TERPANJANG yang
rata-rata elemennya setidaknya X. Cetak panjangnya, atau 0 jika tidak ada.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= a[i], X <= 10^9

SAMPLE INPUT 1:
5 3
1 5 2 6 4

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
    // Kurangi setiap elemen dengan X. Sekarang syaratnya jumlah segmen >= 0. Cari segmen terpanjang dengan jumlah non-negatif memakai prefix + minimum prefix di kiri.

    return 0;
}
