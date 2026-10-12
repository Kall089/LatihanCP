/*
============================================================
🏋️ Exercise 4: First and Last Position (LeetCode 34)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Cari posisi pertama dan terakhir dari target X pada array terurut A.
Jika target tidak ditemukan, cetak "-1 -1".

📎 SAMPLE INPUT:
6 8
5 7 7 8 8 10

📎 SAMPLE OUTPUT:
3 4
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

    // TODO: Hitung first_idx dan last_idx
    int first_idx = -1, last_idx = -1;

    cout << first_idx << " " << last_idx << "\n";

    return 0;
}
