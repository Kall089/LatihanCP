/*
============================================================
📋 TUGAS 06: Target Sum Expressions
============================================================
Source: LeetCode 494 style
Difficulty: Medium
Topics: target transform, counting subset sum

PROBLEM:
Diberikan N bilangan non-negatif dan target T. Untuk setiap bilangan, pilih
tanda + atau -. Hitung banyak cara pemberian tanda sehingga hasil ekspresi
sama dengan T. Cetak jawaban modulo 1.000.000.007.

INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan A[i]

OUTPUT FORMAT:
- Banyak cara modulo 1.000.000.007

CONSTRAINTS:
- 1 <= N <= 200
- -100000 <= T <= 100000
- 0 <= A[i] <= 1000

SAMPLE INPUT 1:
5 3
1 1 1 1 1

SAMPLE OUTPUT 1:
5

HINT:
Jika subset bertanda positif punya sum P dan total semua angka adalah S,
maka P - (S-P) = T, sehingga P = (S+T)/2.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Validasi S+T, lalu hitung subset sum target (S+T)/2.

    return 0;
}
