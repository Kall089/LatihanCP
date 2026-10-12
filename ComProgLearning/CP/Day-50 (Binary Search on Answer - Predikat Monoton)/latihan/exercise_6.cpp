/*
============================================================
🏋️ Exercise 6: Floating Point Binary Search (Square Root Precision)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search on Real Numbers
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Hitung nilai sqrt(N) untuk bilangan real N dengan presisi 6 tempat desimal menggunakan Binary Search 100 iterasi.

📎 SAMPLE INPUT:
2.0

📎 SAMPLE OUTPUT:
1.414214
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double n;
    if (!(cin >> n)) return 0;

    // TODO: Implementasi 100-step binary search pada double
    double ans = 0;

    cout << fixed << setprecision(6) << ans << "\n";

    return 0;
}
