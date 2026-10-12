/*
============================================================
📋 TUGAS 07: Two Sets Counting
============================================================
Source: CSES 1093 inspired
Difficulty: Medium
Topics: counting partition, modulo

PROBLEM:
Diberikan bilangan N. Pertimbangkan set {1, 2, ..., N}. Hitung banyak cara
membagi set tersebut menjadi dua subset dengan jumlah sama. Dua pembagian
yang hanya tertukar sisi dianggap sama. Cetak jawaban modulo 1.000.000.007.

INPUT FORMAT:
- Satu bilangan N

OUTPUT FORMAT:
- Banyak pembagian valid modulo 1.000.000.007

CONSTRAINTS:
- 1 <= N <= 500

SAMPLE INPUT 1:
7

SAMPLE OUTPUT 1:
4

HINT:
Total harus genap. Hitung banyak subset dengan sum total/2, lalu bagi dua
karena setiap partisi dihitung dua kali.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Count subset sum total/2 untuk angka 1..N, lalu kalikan inv2 modulo MOD.

    return 0;
}
