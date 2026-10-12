/*
============================================================
📋 Tugas 10: Count Negatives in Sorted Matrix (LeetCode 1351)
============================================================
Day: 48 | Difficulty: Easy/Medium
Topic: Binary Search per Baris

PROBLEM STATEMENT:
Diberikan matriks M berukuran R x C di mana setiap baris terurut secara DESCENDING.
Hitung total berapa banyak bilangan NEGATIF (< 0) yang ada di dalam matriks tersebut.

INPUT FORMAT:
- Baris 1: R C
- R baris berikutnya: Masing-masing C integer (sorted descending)

OUTPUT FORMAT:
- Satu integer: total jumlah bilangan negatif di matriks.

CONSTRAINTS:
- 1 ≤ R, C ≤ 500
- -10^9 ≤ M[i][j] ≤ 10^9

SAMPLE INPUT 1:
4 4
4 3 2 -1
3 2 1 -1
1 1 -1 -2
-1 -1 -2 -3

SAMPLE OUTPUT 1:
8

PENJELASAN SAMPLE 1:
Baris 1: -1 (1 buah)
Baris 2: -1 (1 buah)
Baris 3: -1, -2 (2 buah)
Baris 4: -1, -1, -2, -3 (4 buah)
Total = 1 + 1 + 2 + 4 = 8.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    int ans = 0;
    for (int i = 0; i < r; i++) {
        vector<long long> row(c);
        for (int j = 0; j < c; j++) cin >> row[j];
        // TODO: Gunakan binary search per baris untuk menghitung elemen < 0
    }

    cout << ans << "\n";

    return 0;
}
