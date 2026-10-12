/*
============================================================
📋 TUGAS 11: Partisi Himpunan Menjadi Tiga Bagian Sama Rata
============================================================
Source: Classic DP / 3-Partition Problem
Difficulty: Medium-Hard
Topics: Multi-dimensional Subset Sum, Reachability

PROBLEM:
Diberikan N buah bilangan bulat positif a[0], ..., a[N-1].
Tentukan apakah himpunan ini dapat dibagi menjadi TIGA SUBSET YANG DISJOIN (saling lepas)
sedemikian sehingga JUMLAH ELEMEN KETIGA SUBSET ADALAH PERSIS SAMA!
Cetak "YA" jika bisa, atau "TIDAK" jika tidak bisa.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
"YA" atau "TIDAK".

CONSTRAINTS:
1 <= N <= 50
Total jumlah elemen <= 600

SAMPLE INPUT 1:
5
1 3 4 2 2

SAMPLE OUTPUT 1:
YA
(Total = 12, target tiap bagian = 4. Subset: {4}, {1, 3}, {2, 2})

SAMPLE INPUT 2:
3
1 2 4

SAMPLE OUTPUT 2:
TIDAK
(Total = 7, tidak habis dibagi 3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan 3-Partition dengan 2D subset sum dp[s1][s2]

    return 0;
}
