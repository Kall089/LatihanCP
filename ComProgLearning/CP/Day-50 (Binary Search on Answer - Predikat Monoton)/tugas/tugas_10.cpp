/*
============================================================
📋 Tugas 10: Divide Chocolate (LeetCode 1231)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search on Answer (Maksimalkan Minimum Portion)

PROBLEM STATEMENT:
Kamu memiliki batang cokelat yang terdiri dari N potong dengan tingkat manis M[1..N].
Kamu harus membagi cokelat ini kepada dirimu dan K orang temanmu (total K + 1 orang) dengan cara memotongnya menjadi K + 1 bagian kontigu.
Sebagai orang yang baik hati, kamu akan mengambil bagian dengan TOTAL MANIS TERKECIL di antara K + 1 bagian tersebut.
Maksimalkan total manis bagian yang KAMU dapatkan!

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N integer M[1..N]

OUTPUT FORMAT:
- Satu integer: total manis maksimum dari bagian terkecil.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 0 ≤ K < N
- 1 ≤ M[i] ≤ 10^5

SAMPLE INPUT 1:
9 5
1 2 2 1 2 2 1 2 2

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
Bagi menjadi 6 bagian: [1,2], [2,1], [2,2], [1,2], [2]. Manis tiap bagian >= 3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> m(n);
    for (int i = 0; i < n; i++) cin >> m[i];

    // TODO: Binary search pada total manis bagian minimum

    return 0;
}
