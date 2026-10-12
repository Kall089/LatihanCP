/*
============================================================
✅ Solution 3: Potong Kayu (SPOJ EKO)
============================================================
Approach: Binary Search on Answer (Maksimalkan Tinggi H)
Complexity: Time O(N log(max_H)) | Space O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool check(long long height, const vector<long long>& h, long long target_wood) {
    long long wood = 0;
    for (long long tree : h) {
        if (tree > height) {
            wood += (tree - height);
        }
    }
    return wood >= target_wood;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> h(n);
    long long max_h = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        max_h = max(max_h, h[i]);
    }

    long long low = 0, high = max_h;
    long long ans = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, h, m)) {
            ans = mid;
            low = mid + 1; // Coba gergaji lebih tinggi
        } else {
            high = mid - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
