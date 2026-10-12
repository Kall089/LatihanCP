/*
============================================================
✅ Solution 6: Next Greater Element (Monotonic Stack)
============================================================
Approach: Monotonic stack (decreasing)
Complexity: Time O(N) | Space O(N)
Key Insight: Stack stores indices of elements waiting for their
             "next greater". When we find a greater element,
             we pop all smaller elements and assign their answer.

📖 PENJELASAN PENDEKATAN:
1. result[i] = -1 untuk semua i (default: no greater)
2. Stack stores indices with decreasing values
3. For each i:
   a. While stack not empty AND arr[top] < arr[i]:
      - result[top] = arr[i] (found next greater!)
      - pop
   b. Push i
4. Remaining in stack have no next greater (already -1)

🔄 ALTERNATIVE APPROACHES:
- Brute force O(N²): for each i, scan right — TLE
- Iterate from right with stack: same O(N), slightly different logic
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<int> result(n, -1);
    stack<int> st;  // stores indices

    for (int i = 0; i < n; i++) {
        // Pop all elements that are smaller than current
        while (!st.empty() && a[st.top()] < a[i]) {
            result[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << result[i];
    }
    cout << '\n';

    return 0;
}
