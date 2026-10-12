/*
============================================================
📋 Tugas 15: Maximum Running Time of N Computers (LeetCode 2141)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search on Answer + Greedy Capacity Check

PROBLEM STATEMENT:
Kamu punya N komputer dan M baterai dengan kapasitas B[1..M] jam.
Kamu ingin mengoperasikan SEMUA N komputer SECARA BERSAMAAN selama mungkin.
Kamu boleh memindahkan baterai antar komputer kapan saja secara instan.
Maksimalkan jumlah jam N komputer bisa menyala bersamaan!

INPUT FORMAT:
- Baris 1: N M
- Baris 2: M integer B[1..M]

OUTPUT FORMAT:
- Satu integer: waktu nyala maksimum dalam jam.

CONSTRAINTS:
- 1 ≤ N ≤ M ≤ 100.000
- 1 ≤ B[i] ≤ 10^9

SAMPLE INPUT 1:
2 3
3 3 3

SAMPLE OUTPUT 1:
4

PENJELASAN SAMPLE 1:
Dengan 3 baterai berkapasitas 3 jam, 2 komputer bisa menyala selama 4 jam.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    // TODO: Binary search pada waktu T. Dalam check(T), sum(min(b[i], T)) >= N * T

    return 0;
}
