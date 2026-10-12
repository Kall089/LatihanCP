/*
============================================================
✅ Solution 5: Capacity To Ship Packages Within D Days
============================================================
Approach: Binary Search on Answer
Complexity: Time O(N log(sum_W)) | Space O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool check(long long cap, const vector<long long>& w, int d) {
    int days = 1;
    long long load = 0;
    for (long long weight : w) {
        if (weight > cap) return false;
        if (load + weight > cap) {
            days++;
            load = weight;
        } else {
            load += weight;
        }
    }
    return days <= d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d;
    if (!(cin >> n >> d)) return 0;

    vector<long long> w(n);
    long long max_w = 0, sum_w = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        max_w = max(max_w, w[i]);
        sum_w += w[i];
    }

    long long low = max_w, high = sum_w;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, w, d)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
