/*
============================================================
✅ Solution 6: Search in Rotated Sorted Array (LeetCode 33)
============================================================
Approach: Modified Binary Search (Cek bagian mana yang terurut)
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
        }

        // Cek apakah separuh kiri terurut
        if (a[low] <= a[mid]) {
            if (a[low] <= x && x < a[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Separuh kanan terurut
            if (a[mid] < x && x <= a[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
