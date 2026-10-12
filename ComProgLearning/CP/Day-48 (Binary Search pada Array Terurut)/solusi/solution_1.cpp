/*
============================================================
✅ Solution 1: Binary Search Standard
============================================================
Approach: Standard Binary Search
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

    int low = 0, high = n - 1;
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) {
            ans = mid;
            break;
        } else if (a[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
