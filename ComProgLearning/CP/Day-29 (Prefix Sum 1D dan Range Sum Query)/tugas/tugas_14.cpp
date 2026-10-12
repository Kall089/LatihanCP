/*
============================================================
📋 TUGAS 14: Prefix Sum dengan Update Jarang
============================================================
Source: Original
Difficulty: Hard
Topics: rebuild berkala / sqrt

PROBLEM:
Diberikan array N bilangan, Q operasi berupa: '1 i x' (ubah a[i] jadi x)
atau '2 l r' (cetak jumlah a[l..r]). Dijamin banyaknya operasi tipe 1
paling banyak 300.
Selesaikan TANPA Fenwick Tree — manfaatkan bahwa update sangat jarang.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi tipe 2

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5
- banyak operasi tipe 1 <= 300

SAMPLE INPUT 1:
4 3
1 2 3 4
2 1 4
1 2 10
2 1 4

SAMPLE OUTPUT 1:
10
18
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bangun ulang prefix setiap ada update: 300 * 2*10^5 = 6*10^7, masih aman. Atau simpan daftar delta.

    return 0;
}
