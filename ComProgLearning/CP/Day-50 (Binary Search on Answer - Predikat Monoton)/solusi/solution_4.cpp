/*
============================================================
✅ Solution 4: Array Division
============================================================
Approach: Binary Search on Answer + Greedy Check
Complexity: Time O(N log(sum_A)) | Space O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool check(long long max_sum, const vector<long long>& a, int k) {
    int count = 1;
    long long current_sum = 0;
    for (long long x : a) {
        if (x > max_sum) return false; // Elemen tunggal sudah melebihi
        if (current_sum + x > max_sum) {
            count++;
            current_sum = x;
        } else {
            current_sum += x;
        }
    }
    return count <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    long long max_elem = 0, sum_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        max_elem = max(max_elem, a[i]);
        sum_a += a[i];
    }

    long long low = max_elem, high = sum_a;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, a, k)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
