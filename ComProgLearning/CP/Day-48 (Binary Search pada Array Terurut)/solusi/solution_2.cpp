/*
============================================================
✅ Solution 2: Lower Bound & Upper Bound Manual
============================================================
Approach: Binary Search Range Elimination
Complexity: Time O(log N) | Space O(1)
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

    // Lower bound: first index where a[i] >= x
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= x) high = mid;
        else low = mid + 1;
    }
    int lb = low;

    // Upper bound: first index where a[i] > x
    low = 0; high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] > x) high = mid;
        else low = mid + 1;
    }
    int ub = low;

    cout << lb << " " << ub << "\n";

    return 0;
}
