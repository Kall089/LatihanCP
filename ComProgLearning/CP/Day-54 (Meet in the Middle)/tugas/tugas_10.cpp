/*
============================================================
📋 TUGAS 10: Split Array With Same Average
============================================================
Source: LeetCode 805
Difficulty: Hard
Topics: MITM + rata-rata

PROBLEM:
Diberikan array N bilangan, tentukan apakah array itu bisa dibagi menjadi
dua bagian tidak kosong yang RATA-RATANYA sama. Cetak YA atau TIDAK.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- YA atau TIDAK

CONSTRAINTS:
- 1 <= N <= 30
- 0 <= a[i] <= 10^4

SAMPLE INPUT 1:
6
1 2 3 4 5 6

SAMPLE OUTPUT 1:
YA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Rata-rata sama berarti kedua bagian punya rata-rata yang sama dengan keseluruhan. Kurangi setiap elemen dengan rata-rata (kalikan N dulu agar bilangan bulat), lalu cari subhimpunan tidak kosong berjumlah nol.

    return 0;
}
