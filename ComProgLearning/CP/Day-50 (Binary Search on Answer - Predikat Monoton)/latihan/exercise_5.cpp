/*
============================================================
🏋️ Exercise 5: Capacity To Ship Packages Within D Days (LeetCode 1011)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada paket-paket berbobot W[1..N] yang harus dikirim secara urut dalam D hari.
Minimalkan kapasitas muatan kapal sedemikian hingga seluruh paket terkirim dalam <= D hari.

📎 SAMPLE INPUT:
10 5
1 2 3 4 5 6 7 8 9 10

📎 SAMPLE OUTPUT:
15
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    if (!(cin >> n >> d)) return 0;

    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];

    // TODO: Implementasi binary search pada kapasitas kapal
    long long ans = 0;

    cout << ans << "\n";

    return 0;
}
