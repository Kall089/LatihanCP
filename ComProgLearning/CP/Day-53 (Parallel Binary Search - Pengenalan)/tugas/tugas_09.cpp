/*
============================================================
📋 TUGAS 09: Ambang Bertahap
============================================================
Source: Original
Difficulty: Hard
Topics: PBS + multiset

PROBLEM:
Ada N kejadian; kejadian ke-t menyisipkan bilangan x[t] ke dalam sebuah
himpunan (duplikat diperbolehkan). Untuk setiap query (k, T), cari kejadian
keberapa bilangan terkecil ke-k di dalam himpunan menjadi tidak lebih dari
T. Cetak -1 kalau tidak pernah.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan x[t]
- Q baris: k dan T

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 2
5 3 8 1 9
2 4
1 0

SAMPLE OUTPUT 1:
4
-1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Predikatnya monoton karena himpunan hanya bertambah. Pakai BIT atas nilai terkompresi untuk menghitung berapa elemen <= T.

    return 0;
}
