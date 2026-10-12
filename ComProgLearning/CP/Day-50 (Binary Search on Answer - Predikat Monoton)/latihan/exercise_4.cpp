/*
============================================================
🏋️ Exercise 4: Array Division (CSES Array Division)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Bagi array A yang terdiri dari N elemen menjadi K subarray tak kosong kontigu.
Minimalkan nilai MAXIMUM SUBARRAY SUM di antara K bagian tersebut.

📎 SAMPLE INPUT:
5 3
2 4 7 3 5

📎 SAMPLE OUTPUT:
8
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Binary search pada max subarray sum
    long long ans = 0;

    cout << ans << "\n";

    return 0;
}
