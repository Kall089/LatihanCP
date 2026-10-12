/*
============================================================
📋 TUGAS 08: Jalur Paling Andal
============================================================
Source: Klasik (maximum probability path)
Difficulty: Medium
Topics: max-heap, operator perkalian

PROBLEM:
Graf tak berarah; setiap edge punya probabilitas p (0 <= p <= 1) bahwa jalur
itu aman. Keandalan sebuah jalur = HASIL KALI probabilitas edge-nya. Cari
keandalan MAKSIMUM dari 1 ke N. Cetak 6 angka di belakang koma; 0.000000 jika
tak terjangkau.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b p

OUTPUT FORMAT:
- satu bilangan desimal

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    0.250000
1 2 0.5
2 3 0.5
1 3 0.2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    1.000000
1 2 1.0

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    0.000000
1 2 0.9
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // MAX-heap, dist[v] = max(dist[v], dist[u] * p), dist[1] = 1.0.
    // Valid karena 0 <= p <= 1: perkalian tidak pernah MEMBESARKAN nilai --
    // sifat monoton yang sama dengan "bobot non-negatif".
    return 0;
}
