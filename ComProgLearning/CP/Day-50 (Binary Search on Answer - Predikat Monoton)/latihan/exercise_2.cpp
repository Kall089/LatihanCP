/*
============================================================
🏋️ Exercise 2: Aggressive Cows (SPOJ AGGRCOW)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kandang di posisi X[1..N]. Ada C ekor sapi yang ingin ditempatkan di kandang.
Tiap kandang hanya bisa menampung 1 sapi. Maksimalkan JARAK MINIMUM antar sapi!

📎 SAMPLE INPUT:
5 3
1 2 8 4 9

📎 SAMPLE OUTPUT:
3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    if (!(cin >> n >> c)) return 0;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    // TODO: Sort posisi dan binary search pada jarak minimum
    long long ans = 0;

    cout << ans << "\n";

    return 0;
}
