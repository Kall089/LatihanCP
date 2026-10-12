/*
============================================================
🏋️ Exercise 6: Search in Rotated Sorted Array (LeetCode 33)
============================================================
Day: 48 | Difficulty: Hard
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Array A terurut secara ascending tetapi di-rotate pada sebuah pivot tak diketahui.
Cari indeks target X di dalam array tersebut dalam O(log N). Jika tidak ada, cetak -1.

📎 SAMPLE INPUT:
7 0
4 5 6 7 0 1 2

📎 SAMPLE OUTPUT:
4
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

    // TODO: Implementasi pencarian biner pada rotated sorted array
    int ans = -1;

    cout << ans << "\n";

    return 0;
}
