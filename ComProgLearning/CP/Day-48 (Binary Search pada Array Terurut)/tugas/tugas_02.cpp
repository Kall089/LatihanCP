/*
============================================================
📋 Tugas 02: Count Less Than or Equal
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search / Upper Bound

PROBLEM STATEMENT:
Diberikan array A berukuran N terurut ascending.
Diberikan Q pertanyaan, masing-masing berupa integer X.
Hitung berapa banyak elemen di A yang nilainya LEBIH KECIL ATAU SAMA DENGAN X (A[i] ≤ X).

INPUT FORMAT:
- Baris 1: N Q
- Baris 2: N buah integer A[i] (sorted)
- Q baris berikutnya: Masing-masing berisi integer X

OUTPUT FORMAT:
- Untuk setiap query, cetak jumlah elemen ≤ X.

CONSTRAINTS:
- 1 ≤ N, Q ≤ 100.000
- -10^9 ≤ A[i], X ≤ 10^9

SAMPLE INPUT 1:
5 3
1 2 4 4 7
4
0
10

SAMPLE OUTPUT 1:
4
0
5

PENJELASAN SAMPLE 1:
Elemen ≤ 4 ada 4 buah (1, 2, 4, 4).
Elemen ≤ 0 ada 0 buah.
Elemen ≤ 10 ada 5 buah (semua elemen).

HINT:
Gunakan std::upper_bound(A.begin(), A.end(), X) - A.begin().
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
        // TODO: Hitung jumlah elemen <= X menggunakan Upper Bound
    }

    return 0;
}
