/*
============================================================
📋 TUGAS 13: Subset Sum dengan Dua Batas
============================================================
Source: Original
Difficulty: Hard
Topics: MITM dua dimensi

PROBLEM:
N barang dengan dua besaran: berat w[i] dan volume v[i]. Tas punya batas
berat W dan batas volume V. Pilih subhimpunan yang memenuhi KEDUA batas
sehingga jumlah nilai p[i] maksimum.

INPUT FORMAT:
- Baris pertama: N, W, dan V
- N baris: w, v, p

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 30
- 1 <= W, V <= 10^12

SAMPLE INPUT 1:
2 5 5
2 3 10
3 2 20

SAMPLE OUTPUT 1:
30
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dengan DUA batas, pengurutan sederhana tidak cukup - kamu butuh struktur yang mendukung query 'nilai maksimum dengan w <= X dan v <= Y'. Pikirkan sorting + Fenwick tree, atau buang subset yang jelas kalah (dominated).

    return 0;
}
