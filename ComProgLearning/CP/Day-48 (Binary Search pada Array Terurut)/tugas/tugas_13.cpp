/*
============================================================
📋 Tugas 13: First Bad Version (LeetCode 278)
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search First Condition

PROBLEM STATEMENT:
Kamu adalah produk manajer. Versi produk dari 1 sampai N diuji.
Diberikan array B berukuran N+1 (1-indexed) di mana B[i] = 0 menandakan versi BAIK,
dan B[i] = 1 menandakan versi RUSAK.
Jika suatu versi rusak, maka SEMUA versi setelahnya juga pasti rusak.
Cari versi rusak PERTAMA.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N integer (0 atau 1)

OUTPUT FORMAT:
- Satu integer: nomor versi rusak pertama (1-indexed).

CONSTRAINTS:
- 1 ≤ N ≤ 100.000

SAMPLE INPUT 1:
5
0 0 0 1 1

SAMPLE OUTPUT 1:
4

PENJELASAN SAMPLE 1:
Versi 1, 2, 3 baik (0). Versi 4 dan 5 rusak (1). Versi rusak pertama adalah 4.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    // TODO: Cari versi 1 pertama menggunakan Binary Search

    return 0;
}
