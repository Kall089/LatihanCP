/*
============================================================
✅ Solution 6: Floating Point Binary Search
============================================================
Approach: Fixed Iteration Binary Search on Double
Complexity: Time O(100) | Space O(1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double n;
    if (!(cin >> n)) return 0;

    double low = 0, high = max(1.0, n);
    for (int iter = 0; iter < 100; iter++) {
        double mid = low + (high - low) / 2.0;
        if (mid * mid >= n) {
            high = mid;
        } else {
            low = mid;
        }
    }

    cout << fixed << setprecision(6) << low << "\n";

    return 0;
}
