/*
============================================================
📋 Tugas 09: Maximum Median (Codeforces 1201C)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Maksimalkan Median)

PROBLEM STATEMENT:
Diberikan array A berukuran N (N selalu ganjil). Kamu memiliki modal maksimal K operasi.
Dalam satu operasi, kamu dapat menambah nilai salah satu elemen sebesar 1.
Maksimalkan NILAI MEDIAN dari array A setelah melakukan maksimal K operasi!

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N integer A[1..N]

OUTPUT FORMAT:
- Satu integer: nilai median maksimum yang mungkin dicapai.

CONSTRAINTS:
- 1 ≤ N ≤ 200.000 (N ganjil)
- 1 ≤ K ≤ 10^9
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
3 2
1 3 5

SAMPLE OUTPUT 1:
5

PENJELASAN SAMPLE 1:
Array sorted: [1, 3, 5]. Median awal = 3.
Tambah 3 sebanyak 2 kali -> [1, 5, 5]. Median baru = 5. Total ops = 2.
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

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Sort A dan lakukan Binary Search pada nilai median target

    return 0;
}
