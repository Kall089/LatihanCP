/*
============================================================
✅ Solution 5: Floor and Ceiling in Sorted Array
============================================================
Approach: Binary Search / Bound lookup
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

    // Ceiling: first element >= x
    auto cl_it = lower_bound(a.begin(), a.end(), x);
    long long cl = (cl_it != a.end()) ? *cl_it : -1;

    // Floor: largest element <= x
    auto fl_it = upper_bound(a.begin(), a.end(), x);
    long long fl = -1;
    if (fl_it != a.begin()) {
        fl = *prev(fl_it);
    }

    cout << fl << " " << cl << "\n";

    return 0;
}
