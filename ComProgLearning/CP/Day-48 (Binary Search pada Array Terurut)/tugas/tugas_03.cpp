/*
============================================================
📋 Tugas 03: Count Strictly Greater Than X
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search / Upper Bound

PROBLEM STATEMENT:
Diberikan array A berukuran N terurut ascending.
Diberikan Q pertanyaan, masing-masing berupa integer X.
Hitung berapa banyak elemen di A yang nilainya STRICTLY LEBIH BESAR DARI X (A[i] > X).

INPUT FORMAT:
- Baris 1: N Q
- Baris 2: N integer A[i]
- Q baris berikutnya: Integer X

OUTPUT FORMAT:
- Q baris: Jumlah elemen > X.

CONSTRAINTS:
- 1 ≤ N, Q ≤ 100.000
- -10^9 ≤ A[i], X ≤ 10^9

SAMPLE INPUT 1:
5 3
1 3 5 7 9
4
9
0

SAMPLE OUTPUT 1:
3
0
5

PENJELASAN SAMPLE 1:
Elemen > 4 ada 3 buah (5, 7, 9).
Elemen > 9 ada 0 buah.
Elemen > 0 ada 5 buah.
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
        // TODO: Hitung jumlah elemen > X (N - upper_bound(x))
    }

    return 0;
}
