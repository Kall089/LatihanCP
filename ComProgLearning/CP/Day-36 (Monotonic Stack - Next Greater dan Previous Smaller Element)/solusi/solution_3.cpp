/*
============================================================
  Solution 3: Previous Smaller Element
============================================================
Kompleksitas: O(n) — monotonic increasing stack
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> pse(n, -1);
    stack<int> st; // menyimpan nilai (bukan index)

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() >= a[i])
            st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(a[i]);
    }

    for (int i = 0; i < n; i++)
        cout << pse[i] << " \n"[i == n-1];
    return 0;
}
