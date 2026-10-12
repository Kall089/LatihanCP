/*
============================================================
✅ Solution 4: First and Last Position (LeetCode 34)
============================================================
Approach: Dual Binary Search / Bound checking
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

    auto lb = lower_bound(a.begin(), a.end(), x);
    if (lb == a.end() || *lb != x) {
        cout << "-1 -1\n";
        return 0;
    }

    auto ub = upper_bound(a.begin(), a.end(), x);
    int first_idx = distance(a.begin(), lb);
    int last_idx = distance(a.begin(), ub) - 1;

    cout << first_idx << " " << last_idx << "\n";

    return 0;
}
