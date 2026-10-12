/*
============================================================
📋 Tugas 05: Closest Element to Target
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search / Boundary Check

PROBLEM STATEMENT:
Diberikan array A terurut berukuran N dan target X.
Cari nilai elemen di A yang memiliki selisih mutlak |A[i] - X| terkecil.
Jika terdapat dua elemen dengan selisih terkecil yang sama, cetak nilai yang lebih kecil.

INPUT FORMAT:
- Baris 1: N X
- Baris 2: N integer terurut A[i]

OUTPUT FORMAT:
- Satu integer: nilai elemen di A yang paling dekat dengan X.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- -10^9 ≤ A[i], X ≤ 10^9

SAMPLE INPUT 1:
5 4
1 2 7 8 9

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
5 5
1 2 8 9 10

SAMPLE OUTPUT 2:
2

PENJELASAN SAMPLE 1:
|1-4|=3, |2-4|=2, |7-4|=3, |8-4|=4, |9-4|=5.
Selisih terkecil adalah 2 (elemen nilai 2).

PENJELASAN SAMPLE 2:
|2-5|=3 dan |8-5|=3. Keduanya berselisih 3. Pilih yang lebih kecil (2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Cari elemen dengan selisih mutlak terdekat

    return 0;
}
