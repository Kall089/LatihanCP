/*
============================================================
📋 TUGAS 10: Concert Tickets
============================================================
Source: CSES 1091
Difficulty: Medium
Topics: multiset

PROBLEM:
Ada N tiket dengan harga masing-masing, dan M pelanggan dengan harga
maksimum yang mereka bersedia bayar. Setiap pelanggan membeli tiket
TERMAHAL yang harganya tidak melebihi batasnya. Cetak harga yang dibayar
tiap pelanggan, atau -1 kalau tidak ada tiket yang cocok.

INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N harga tiket
- Baris ketiga: M batas harga

OUTPUT FORMAT:
- M baris

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:
5 3
5 3 7 8 5
4 8 3

SAMPLE OUTPUT 1:
3
8
5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // multiset + upper_bound lalu mundur satu. Bukan quickselect, tapi latihan pemilihan yang bagus.

    return 0;
}
