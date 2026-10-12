/*
============================================================
✅ Solution 5: Sliding Window Maximum (Monotonic Deque)
============================================================
Approach: Monotonic deque (decreasing values)
Complexity: Time O(N) | Space O(K)
Key Insight: Maintain deque of indices where values are DECREASING.
             dq.front() = index of maximum in current window.
             Each element is pushed and popped at most once → O(N).

📖 PENJELASAN PENDEKATAN:
1. Deque stores indices, maintaining decreasing arr values
2. For each i:
   a. Remove front if out of window (index <= i - K)
   b. Remove back if arr[back] <= arr[i] (mereka tak mungkin jadi max)
   c. Push i to back
   d. If i >= K-1: output arr[front] (= window max)

🔄 ALTERNATIVE APPROACHES:
- Brute force O(NK): nested loop — TLE for large N
- Multiset: O(N log K) — insert/erase per slide
- Segment tree: O(N log N) — overkill
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    deque<int> dq;  // stores indices, decreasing value order

    for (int i = 0; i < n; i++) {
        // Remove elements outside window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove smaller elements from back (they'll never be max)
        while (!dq.empty() && a[dq.back()] <= a[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Output when window is full
        if (i >= k - 1) {
            if (i > k - 1) cout << ' ';
            cout << a[dq.front()];
        }
    }
    cout << '\n';

    return 0;
}
