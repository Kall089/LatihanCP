/*
============================================================
✅ Solution 1: Factory Machines
============================================================
Approach: Binary Search on Answer (Minimalkan Waktu)
Complexity: Time O(N log(max_time)) | Space O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool check(long long time, const vector<long long>& k, long long target) {
    long long products = 0;
    for (long long time_per_item : k) {
        products += time / time_per_item;
        if (products >= target) return true; // Early exit cegah overflow
    }
    return products >= target;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long t;
    if (!(cin >> n >> t)) return 0;

    vector<long long> k(n);
    long long min_k = 1e18;
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        min_k = min(min_k, k[i]);
    }

    long long low = 1, high = min_k * t;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, k, t)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
