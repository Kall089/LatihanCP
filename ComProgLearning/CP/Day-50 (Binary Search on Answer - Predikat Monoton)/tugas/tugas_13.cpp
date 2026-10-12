/*
============================================================
📋 Tugas 13: Replace the Chalk (LeetCode 1894)
============================================================
Day: 50 | Difficulty: Medium
Topic: Prefix Sum + Binary Search

PROBLEM STATEMENT:
Ada N siswa [0..N-1] duduk melingkar. Siswa ke-i membutuhkan CHALK[i] buah kapur untuk menyelesaikan soal.
Awalnya ada K buah kapur. Proses berjalan melingkar dari siswa 0, 1, ..., N-1, 0, 1...
Tentukan indeks siswa PERTAMA yang TIDAK MENDAPAT CUKUP KAPUR untuk menyelesaikan soalnya.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N integer CHALK[0..N-1]

OUTPUT FORMAT:
- Satu integer: indeks siswa yang kehabisan kapur (0-indexed).

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1 ≤ K ≤ 10^9
- 1 ≤ CHALK[i] ≤ 10^5

SAMPLE INPUT 1:
4 22
5 1 5 4

SAMPLE OUTPUT 1:
0

PENJELASAN SAMPLE 1:
Total kapur 1 putaran = 5 + 1 + 5 + 4 = 15.
Sisa kapur setelah 1 putaran = 22 % 15 = 7.
- Siswa 0 butuh 5 kapur -> sisa 2.
- Siswa 1 butuh 1 kapur -> sisa 1.
- Siswa 2 butuh 5 kapur -> KAPUR HABIS! Siswa 2 yang kena (ops, cek sample output)!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> chalk(n);
    for (int i = 0; i < n; i++) cin >> chalk[i];

    // TODO: Gunakan Prefix Sum + Modulo + Binary Search (upper_bound)

    return 0;
}
