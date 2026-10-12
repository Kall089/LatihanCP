/*
============================================================
📋 TUGAS 11: Coordinate Compression
============================================================
Source: Codeforces-style
Difficulty: Hard
Topics: vector, pair, sort, unique, lower_bound

PROBLEM:
Diberikan N bilangan bulat. Lakukan coordinate compression:
ganti setiap bilangan dengan RANKING-nya (1-indexed) jika semua bilangan
diurutkan dan di-deduplikasi.

Contoh: [100, 5, 30, 5, 100]
Sorted unique: [5, 30, 100] → rank 1, 2, 3
Output: [3, 1, 2, 1, 3]

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu baris: N integer (ranking masing-masing elemen)

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
100 5 30 5 100

SAMPLE OUTPUT:
3 1 2 1 3

SAMPLE INPUT 2:
4
10 20 30 40

SAMPLE OUTPUT 2:
1 2 3 4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Copy vector, sort+unique copy, lalu untuk setiap elemen asli
    //       cari posisinya di sorted unique array pakai lower_bound

    return 0;
}
