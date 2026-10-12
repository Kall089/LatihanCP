/*
============================================================
📋 TUGAS 09: Reconstruct One Subset
============================================================
Source: Practice
Difficulty: Medium
Topics: subset sum, reconstruction

PROBLEM:
Diberikan N bilangan positif dan target S. Jika ada subset yang jumlahnya S,
cetak banyak elemen subset tersebut lalu indeks-indeksnya dalam urutan naik
(1-based). Jika tidak ada, cetak IMPOSSIBLE.

INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N bilangan A[i]

OUTPUT FORMAT:
- Jika tidak bisa: IMPOSSIBLE
- Jika bisa:
  baris pertama: K, banyak elemen yang dipilih
  baris kedua: K indeks 1-based dalam urutan naik

CONSTRAINTS:
- 1 <= N <= 100
- 0 <= S <= 100000
- 1 <= A[i] <= 1000

SAMPLE INPUT 1:
5 12
3 5 7 10 2

SAMPLE OUTPUT 1:
2
2 3

HINT:
DP 2D paling mudah untuk rekonstruksi. Telusuri dari dp[N][S] ke belakang.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Pakai DP 2D atau simpan parent untuk merekonstruksi satu subset.

    return 0;
}
