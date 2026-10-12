/*
============================================================
📋 TUGAS 10: Banyak Jalur Melewati Setiap Edge
============================================================
Source: Varian klasik
Difficulty: Medium
Topics: DP dua arah (prefix * suffix)

PROBLEM:
DAG N simpul, M edge. Untuk SETIAP edge (u,v), hitung ada berapa jalur
1 -> N yang melewati edge tersebut. Cetak M bilangan sesuai urutan input,
modulo 10^9+7.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v

OUTPUT FORMAT:
- M bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 4                    1 1 1 1
1 2
2 4
1 3
3 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    1 1 1
1 2
2 3
1 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
5 5                    1 1 1 1 2
1 2
1 3
2 4
3 4
4 5
Penjelasan: ada 2 jalur (1-2-4-5 dan 1-3-4-5). Edge 4->5 dilewati keduanya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // f[u] = banyak jalur 1 -> u   (DP maju)
    // g[v] = banyak jalur v -> N   (DP di graf terbalik)
    // jawaban untuk edge (u,v) = f[u] * g[v] mod
    return 0;
}
