/*
============================================================
📋 TUGAS 11: Longest Flight Route
============================================================
Source: CSES 1680
Difficulty: Hard
Topics: topo order + DP + rekonstruksi jalur

PROBLEM:
Graf berarah N kota, M penerbangan. Cari rute dari kota 1 ke kota N yang
melewati kota SEBANYAK MUNGKIN. Cetak banyak kota lalu rutenya, atau
"IMPOSSIBLE".

INPUT FORMAT:
- Baris 1: N M
- M baris: a b

OUTPUT FORMAT:
- Baris 1: jumlah kota pada rute
- Baris 2: urutan kota

CONSTRAINTS:
- 2 <= N <= 10^5, 1 <= M <= 2*10^5, graf DAG

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 5                    4
1 2                    1 3 4 5
2 5
1 3
3 4
4 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    2
1 2                    1 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    IMPOSSIBLE
1 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Proses simpul dalam urutan topologis, simpan parent[] untuk rekonstruksi.
    // Simpul yang tidak terjangkau dari 1 harus di-skip (dp = -INF).
    return 0;
}
