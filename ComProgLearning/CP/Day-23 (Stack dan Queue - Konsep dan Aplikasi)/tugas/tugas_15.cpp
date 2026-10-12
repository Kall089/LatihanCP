/*
============================================================
📋 TUGAS 15: Deque — Maximum of All Subarrays of Size K (with Min too)
============================================================
Source: Classic / Codeforces-style
Difficulty: Hard
Topics: deque, monotonic deque, sliding window

PROBLEM:
Diberikan array N bilangan dan integer K. Untuk setiap window
berukuran K, cetak MAXIMUM dan MINIMUM.

OUTPUT berupa dua baris:
- Baris pertama: semua minimum per window
- Baris kedua: semua maximum per window

INPUT:
- Baris pertama: dua integer N dan K
- Baris kedua: N integer

OUTPUT:
- Baris pertama: (N-K+1) integer (minimum per window)
- Baris kedua: (N-K+1) integer (maximum per window)

CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
8 3
1 3 -1 -3 5 3 6 7

SAMPLE OUTPUT:
-1 -3 -3 -3 3 3
3 3 5 5 6 7
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Jalankan dua kali monotonic deque: satu untuk max, satu untuk min.
    //       Atau gabungkan dalam satu pass dengan dua deque.

    return 0;
}
