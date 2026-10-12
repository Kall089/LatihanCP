/*
============================================================
✅ Solution 2: Aggressive Cows
============================================================
Approach: Binary Search on Answer (Maksimalkan Jarak Min) + Greedy
Complexity: Time O(N log N + N log(max_dist)) | Space O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool check(long long dist, const vector<long long>& x, int c) {
    int count = 1;
    long long last_pos = x[0];
    for (size_t i = 1; i < x.size(); i++) {
        if (x[i] - last_pos >= dist) {
            count++;
            last_pos = x[i];
            if (count >= c) return true;
        }
    }
    return count >= c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    if (!(cin >> n >> c)) return 0;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    sort(x.begin(), x.end());

    long long low = 1, high = x.back() - x.front();
    long long ans = 1;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, x, c)) {
            ans = mid;
            low = mid + 1; // Cari jarak yang lebih besar
        } else {
            high = mid - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
