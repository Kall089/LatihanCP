/*
============================================================
📋 TUGAS 15: Semua Simpul yang Terlibat Siklus
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: Kahn + analisis sisa

PROBLEM:
Diberi graf berarah. Cetak semua simpul yang berada DI DALAM suatu siklus
(bukan sekadar bisa mencapai siklus), terurut menaik. Jika tidak ada, cetak
"DAG".

INPUT FORMAT:
- Baris 1: N M
- M baris: u v

OUTPUT FORMAT:
- daftar simpul, atau DAG

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 4                    2 3 4
1 2
2 3
3 4
4 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 2                    DAG
1 2
2 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
5 5                    1 2 3
1 2
2 3
3 1
3 4
4 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Sisa Kahn = simpul di siklus ATAU keturunannya. Untuk menyaring yang
    // BENAR-BENAR di siklus: jalankan Kahn lagi pada subgraf sisa, kali ini
    // memangkas dari arah OUT-degree 0. Atau: pakai SCC (Day 132) dan ambil
    // komponen berukuran >= 2 serta self-loop.
    return 0;
}
