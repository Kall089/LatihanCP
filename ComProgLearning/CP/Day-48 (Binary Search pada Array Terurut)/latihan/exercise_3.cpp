/*
============================================================
🏋️ Exercise 3: Hitung Frekuensi Elemen di Sorted Array
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Hitung berapa banyak elemen bernilai X di dalam array terurut A dalam waktu O(log N).

📎 SAMPLE INPUT:
7 3
1 2 3 3 3 4 5

📎 SAMPLE OUTPUT:
3
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

    // TODO: Gunakan upper_bound - lower_bound
    int freq = 0;

    cout << freq << "\n";

    return 0;
}
