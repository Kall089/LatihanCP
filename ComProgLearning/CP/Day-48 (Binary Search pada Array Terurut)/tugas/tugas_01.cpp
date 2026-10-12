/*
============================================================
📋 Tugas 01: Periksa Keberadaan Nilai
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search Dasar

PROBLEM STATEMENT:
Diberikan array A berukuran N yang sudah terurut secara ascending.
Diberikan Q pertanyaan, masing-masing berisi sebuah integer X.
Untuk setiap pertanyaan, tentukan apakah X ada di dalam array A.

INPUT FORMAT:
- Baris 1: Dua integer N dan Q
- Baris 2: N buah integer terurut A[1], A[2], ..., A[N]
- Q baris berikutnya: Masing-masing berisi satu integer X

OUTPUT FORMAT:
- Cetak Q baris, masing-masing berisi "ADA" jika X terdapat pada A, atau "TIDAK" jika tidak.

CONSTRAINTS:
- 1 ≤ N, Q ≤ 100.000
- -10^9 ≤ A[i], X ≤ 10^9

SAMPLE INPUT 1:
5 3
1 3 5 7 9
5
4
9

SAMPLE OUTPUT 1:
ADA
TIDAK
ADA

PENJELASAN SAMPLE 1:
5 ada di indeks 2 -> ADA.
4 tidak ada di array -> TIDAK.
9 ada di indeks 4 -> ADA.

HINT:
Gunakan binary search manual atau std::binary_search(A.begin(), A.end(), X).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    while (q--) {
        long long x;
        cin >> x;
        // TODO: Cek keberadaan X menggunakan Binary Search
    }

    return 0;
}
