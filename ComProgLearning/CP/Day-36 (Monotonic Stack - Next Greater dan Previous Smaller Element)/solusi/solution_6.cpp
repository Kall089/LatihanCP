/*
============================================================
  Solution 6: Trapping Rain Water
============================================================
Kompleksitas: O(n) waktu, O(n) ruang (precompute)
Alternatif O(1) space: two-pointer approach
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<int> left_max(n), right_max(n);
    left_max[0] = h[0];
    for (int i = 1; i < n; i++)
        left_max[i] = max(left_max[i-1], h[i]);

    right_max[n-1] = h[n-1];
    for (int i = n-2; i >= 0; i--)
        right_max[i] = max(right_max[i+1], h[i]);

    ll total = 0;
    for (int i = 0; i < n; i++) {
        int water = min(left_max[i], right_max[i]) - h[i];
        if (water > 0) total += water;
    }

    cout << total << "\n";
    return 0;
}
