/*
============================================================
📋 Tugas 14: K-th Missing Positive Number (LeetCode 1539)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search pada Array Terurut

PROBLEM STATEMENT:
Diberikan array A berukuran N yang berisi bilangan bulat positif terurut ascending TANPA duplikat.
Cari bilangan bulat positif ke-K yang HILANG (tidak ada) dari array A.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N integer terurut positif A[i]

OUTPUT FORMAT:
- Satu integer: bilangan positif ke-K yang hilang.

CONSTRAINTS:
- 1 ≤ N, K ≤ 100.000
- 1 ≤ A[i] ≤ 100.000

SAMPLE INPUT 1:
5 5
2 3 4 7 11

SAMPLE OUTPUT 1:
9

PENJELASAN SAMPLE 1:
Bilangan positif yang hilang: 1, 5, 6, 8, 9, 10, 12, ...
Bilangan hilang ke-1 = 1
Bilangan hilang ke-2 = 5
Bilangan hilang ke-3 = 6
Bilangan hilang ke-4 = 8
Bilangan hilang ke-5 = 9.

HINT:
Pada indeks i (0-indexed), jumlah bilangan yang hilang sebelum A[i] adalah A[i] - (i + 1).
Lakukan Binary Search untuk menemukan berapa banyak elemen A yang lebih kecil dari bilangan yang dicari.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Cari K-th missing positive number dengan Binary Search

    return 0;
}
