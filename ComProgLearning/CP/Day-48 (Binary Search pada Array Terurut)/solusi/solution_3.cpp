/*
============================================================
✅ Solution 3: Hitung Frekuensi Elemen di Sorted Array
============================================================
Approach: upper_bound - lower_bound
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
    auto ub = upper_bound(a.begin(), a.end(), x);

    int freq = distance(lb, ub);
    cout << freq << "\n";

    return 0;
}
